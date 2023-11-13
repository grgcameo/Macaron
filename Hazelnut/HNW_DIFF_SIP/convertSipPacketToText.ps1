#####################################################
# File Name: convertSipPacketToText.ps1
#####################################################


#####################################################
# variable
#####################################################
Param (
#$TargetVer = (Read-Host -Prompt “Enter Target Version”)
[Parameter(Mandatory=$true)]
$TargetVer
)

#$TargetVer = "HA41"
$ReferenceVer = "HB08"
$InputDir = ".\sample_input"
$OutputRootDir = '.\sample_output'
$OutputDir = "${OutputRootDir}\_output"
$SampleInputZipFile = ".\sample_input.zip"
$SipPacketDir = ".\${TargetVer}"
$WinMergeDiffReferenceDir = "${OutputDir}\reference"
$WinMergeDiffTargetDir =  "${OutputDir}\target"

$TShark = 'C:\Program Files\Wireshark\tshark.exe'
$WinMerge = 'C:\Program Files\WinMerge\WinMergeU.exe'

$CreateCaptureToText = $true
$IgnoreKnownDiff = $true
$StartLocation = Get-Location
#####################################################################################################
# 1. check sample files and prepare for conversion.
#####################################################################################################

# Check to exist $SampleInputZipFile and $SipPacketDir
if (((Get-ChildItem -Path $SampleInputZipFile) -eq $null) -or ((Get-ChildItem -Path $SipPacketDir) -eq $null) -or ((Get-ChildItem -Path $TShark) -eq $null))
{
    exit
}

# Remove sample_input/sample_output directory if present.
if ((Get-ChildItem -Path $OutputRootDir -ErrorAction:Ignore) -ne $null)
{
    Remove-Item -Path $OutputRootDir -Force -Recurse
}

if ((Get-ChildItem -Path $InputDir -ErrorAction:Ignore) -ne $null)
{
    Remove-Item -Path $InputDir -Force -Recurse
}
Expand-Archive -LiteralPath $SampleInputZipFile  -DestinationPath $InputDir

# Extract only file name without extension from packet and Copy packets to the destination directory.
$items = Get-ChildItem -Path $InputDir
foreach($item in $items)
{
    if ($item.PSIsContainer)
    {
        $CopySource = ".\${TargetVer}\{0}.pcapng" -f $item.Name
        $CopyDest = ".\${InputDir}\{0}" -f $item.Name
        #Write-Host ('Copy {0}' -f $item.Name)
        Copy-Item $CopySource -Destination $CopyDest
    }
}
<# 
  # Split-Path with -LeafBase parameter is available in pwershell 7 or higher.
$TargetPackets = Get-ChildItem -Path ".\${TargetVer}"
foreach($packet in $TargetPackets)
{
    if ($packet.PSIsContainer -eq $false)
    {
        #Write-Host ('Copy {0}' -f $packet.Name)
        $NameOfDestDir = Split-Path $packet.Name -LeafBase
        Copy-Item $packet -Destination "${InputDir}\${NameOfDestDir}"
    }
}
#>

#####################################################################################################
# 2. convert and copy
#####################################################################################################

New-Item "${OutputDir}\reference" -ItemType Directory -Force
New-Item "${OutputDir}\target" -ItemType Directory -Force

if($IgnoreKnownDiff -eq $true)
{
    $IgnoreOutputDir = "${OutputRootDir}\_output_useIgnoreKnownDiff"
    New-Item "${IgnoreOutputDir}\reference" -ItemType Directory -Force
    New-Item "${IgnoreOutputDir}\target" -ItemType Directory -Force
    
    $WinMergeDiffReferenceDir = "${IgnoreOutputDir}\reference"
    $WinMergeDiffTargetDir =  "${IgnoreOutputDir}\target"
}

#$items = Get-ChildItem
$items = Get-ChildItem -Path $InputDir
foreach($item in $items)
{
    if($item.PSIsContainer)
    {
        Write-Host ('Create {0}' -f $item.Name)

        # Path information for each file.
        $PcapngFile = "${InputDir}\{0}\{0}.pcapng" -f $item.Name
        $ReferenceVerTextFile = "${InputDir}\{0}\{0}_{1}.txt" -f $item.Name, $ReferenceVer
        $TargetVerTextFile = "${InputDir}\{0}\{0}_{1}.txt" -f $item.Name, $TargetVer
        $ReferenceVerTextFilePreprocessing = "${OutputDir}\reference\{0}.txt" -f $item.Name
        $TargetVerTextFilePreprocessing = "${OutputDir}\target\{0}.txt" -f $item.Name

        if($IgnoreKnownDiff -eq $true)
        {
            $ReferenceVerIgnoreKnownDiffTextFilePreprocessing = "${IgnoreOutputDir}\reference\{0}.txt" -f $item.Name
            $TargetVerIgnoreKnownDiffTextFilePreprocessing = "${IgnoreOutputDir}\target\{0}.txt" -f $item.Name
        }

        if($CreateCaptureToText -eq $true)
        {
            #####################################################
            # Create the target text file from the capture file.
            #####################################################
            #$buf = & $TShark -r $PcapngFile -Y sip -T fields -e raw_sip           #  not working
            $buf = & $TShark -r $PcapngFile -Y sip -T fields -e sip.Request-Line -e sip.Status-Line -e sip.msg_hdr
            
            # To Do: Needs some more improvement.
            $buf = $buf -replace "`t", "`r`n"
            $buf = $buf -replace "`r`n`r`n", "`r`n"
            $buf = $buf -replace "`r`nSIP/2.0", "SIP/2.0"
            $buf = $buf -replace "\\t", "."
            $buf = $buf -replace "\\r\\n,", "`r`n"
            $buf = $buf -replace "\\r\\n", "`r`n"
            $buf = $buf -replace "\r\n\r\n", "`r`n`r`n"
            #$buf = $buf -replace "\r\n\r\n\r\n", "`r`n`r`n"
            $buf[-1] = $buf[-1] -replace "\r\n\r\n", ""

            $buf | Out-File $TargetVerTextFile
        }

        # reference : HB08
        $result = Get-Content "$ReferenceVerTextFile"
        $result | Set-Content -Path "$ReferenceVerTextFilePreprocessing"

        if($IgnoreKnownDiff -eq $true)
        {
            #########################################
            # Ignore known differential information.
            #########################################
            $result = $result -replace "Call-ID: .*","Call-ID: [CALL-ID]" # If the Call-ID is incorrect, it is ignored because it does not work correctly in the first place.
            #$result = $result -replace "Call-ID: [0-9,a-z,A-Z,., ,@,-]+","Call-ID: [CALL-ID]"
            $result = $result -replace "\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}","[IPADDR]"
            $result = $result -replace "^Date: (Sun|Mon|Tue|Wed|Thu|Fri|Sat), [0-9]+ (Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec) [0-9]+ \d{1,2}:\d{1,2}:\d{1,2} GMT","Date: [DATETIME]"
            $result = $result -replace ":[0-9]+@",":[NUM1]@"
            $result = $result -replace " [0-9]+ "," [NUM2] "
            $result = $result -replace " [0-9]+ "," [NUM3] "
            $result = $result -replace "branch=[0-9,a-z,A-Z,.,-]+$","branch=[BRANCH]"
            $result = $result -replace "tag=[\w]+","tag=[TAG]"
            $result = $result -replace ";tag=\[TAG\];tag=\[TAG\]",";tag=[TAG]"
            $result = $result -replace "User-Agent: $ReferenceVer","User-Agent: [USER-AGENT]" # If it is the version specified in $ReferenceVer, it will be replaced. 
            $result = $result -replace "Server: $ReferenceVer","Server: [SERVER]"             # If it is the version specified in $ReferenceVer, it will be replaced. 
            $result = $result -replace "<tel:[0-9]+>","<tel:[TEL-NUMBER]>"
            $result = $result -replace "Content-Length: +[0-9]+$","Content-Length: [CONTENT-LENGTH]$"
            $result = $result -replace "^\\trealm=",".realm="
            $result = $result -replace "^\\tnonce=",".nonce="
            $result = $result -replace "^\\turi=",".uri="
            $result = $result -replace "^\\tresponse=",".response="
            $result = $result -replace 'nonce="[0-9,a-z,A-Z]+"','nonce="[NONCE]"'
            $result = $result -replace 'response="[0-9,a-z,A-Z]+"','response="[RESPONSE]"'
            $result = $result -replace '^Proxy-Authorization: Digest username="[0-9,a-z,A-Z]+",$','Proxy-Authorization: Digest username="[USERNAME]",'
            $result = $result -replace 'From: "[0-9]+"','From: "[FROM]"'
            $result = $result -replace 'To: "[0-9]+"','To: "[TO]"'
            $result = $result -replace "^RSeq: [0-9]+$","RSeq: [RSEQ]"
            $result = $result -replace "^Max-Forwards: [0-9]+$","Max-Forwards: [MAX-FORWARDS]"

            $result | Set-Content -Path "$ReferenceVerIgnoreKnownDiffTextFilePreprocessing"
        }

        # target : new SW version to check
        #       ex> HA50, HB09, HC01 ...
        $result = Get-Content "$TargetVerTextFile"
        $result | Set-Content -Path "$TargetVerTextFilePreprocessing"

        if($IgnoreKnownDiff -eq $true)
        {
            #########################################
            # Ignore known differential information.
            #########################################
            $result = $result -replace "Call-ID: .*","Call-ID: [CALL-ID]" # If the Call-ID is incorrect, it is ignored because it does not work correctly in the first place.
            #$result = $result -replace "Call-ID: [0-9,a-z,A-Z,., ,@,-]+","Call-ID: [CALL-ID]"
            $result = $result -replace "\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}","[IPADDR]"
            $result = $result -replace "^Date: (Sun|Mon|Tue|Wed|Thu|Fri|Sat), [0-9]+ (Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec) [0-9]+ \d{1,2}:\d{1,2}:\d{1,2} GMT","Date: [DATETIME]"
            $result = $result -replace ":[0-9]+@",":[NUM1]@"
            $result = $result -replace " [0-9]+ "," [NUM2] "
            $result = $result -replace " [0-9]+ "," [NUM3] "
            $result = $result -replace "branch=[0-9,a-z,A-Z,.,-]+$","branch=[BRANCH]"
            $result = $result -replace "tag=[\w]+","tag=[TAG]"
            $result = $result -replace ";tag=\[TAG\];tag=\[TAG\]",";tag=[TAG]"
            $result = $result -replace "User-Agent: $TargetVer","User-Agent: [USER-AGENT]" # If it is the version specified in $TargetVer, it will be replaced. 
            $result = $result -replace "Server: $TargetVer","Server: [SERVER]"             # If it is the version specified in $TargetVer, it will be replaced. 
            $result = $result -replace "<tel:[0-9]+>","<tel:[TEL-NUMBER]>"
            $result = $result -replace "Content-Length: +[0-9]+$","Content-Length: [CONTENT-LENGTH]$"
            $result = $result -replace "^\\trealm=",".realm="
            $result = $result -replace "^\\tnonce=",".nonce="
            $result = $result -replace "^\\turi=",".uri="
            $result = $result -replace "^\\tresponse=",".response="
            $result = $result -replace 'nonce="[0-9,a-z,A-Z]+"','nonce="[NONCE]"'
            $result = $result -replace 'response="[0-9,a-z,A-Z]+"','response="[RESPONSE]"'
            $result = $result -replace '^Proxy-Authorization: Digest username="[0-9,a-z,A-Z]+",$','Proxy-Authorization: Digest username="[USERNAME]",'
            $result = $result -replace 'From: "[0-9]+"','From: "[FROM]"'
            $result = $result -replace 'To: "[0-9]+"','To: "[TO]"'
            $result = $result -replace "^RSeq: [0-9]+$","RSeq: [RSEQ]"
            $result = $result -replace "^Max-Forwards: [0-9]+$","Max-Forwards: [MAX-FORWARDS]"

            $result | Set-Content -Path "$TargetVerIgnoreKnownDiffTextFilePreprocessing"
        }
    }
}

#####################################################################################################
# 3. run winmerge for diff
#####################################################################################################
if ((Get-ChildItem -Path $WinMerge -ErrorAction:Ignore) -ne $null)
{
    & $WinMerge $WinMergeDiffReferenceDir $WinMergeDiffTargetDir
}

Set-Location $StartLocation