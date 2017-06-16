/****************************************************************************
*
*  Copyright (c) 2000-2013 Broadcom Corporation
*
*  This program is the proprietary software of Broadcom Corporation and/or
*  its licensors, and may only be used, duplicated, modified or distributed
*  pursuant to the terms and conditions of a separate, written license
*  agreement executed between you and Broadcom (an "Authorized License").
*  Except as set forth in an Authorized License, Broadcom grants no license
*  (express or implied), right to use, or waiver of any kind with respect to
*  the Software, and Broadcom expressly reserves all rights in and to the
*  Software and all intellectual property rights therein.  IF YOU HAVE NO
*  AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY,
*  AND SHOULD IMMEDIATELY NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE
*  SOFTWARE.
*
*  Except as expressly set forth in the Authorized License,
*
*  1.     This program, including its structure, sequence and organization,
*  constitutes the valuable trade secrets of Broadcom, and you shall use all
*  reasonable efforts to protect the confidentiality thereof, and to use this
*  information only in connection with your use of Broadcom integrated circuit
*  products.
*
*  2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED
*  "AS IS" AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS
*  OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
*  RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL
*  IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR
*  A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET
*  ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME
*  THE ENTIRE RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
*
*  3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM
*  OR ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL,
*  INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY
*  RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM
*  HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN
*  EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1,
*  WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY
*  FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.
*
****************************************************************************
*
*    Filename: locale.cpp
*
****************************************************************************
*    Description:
*
*     The utility generates a locale configuration file based on input
*     from the make command line.
*
****************************************************************************/

/* ---- Include Files ---------------------------------------------------- */

#ifdef WIN32
#include <tchar.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <unistd.h>
#include <direct.h>

/* ---- Public Variables ------------------------------------------------- */
/* ---- Private Constants and Types -------------------------------------- */

/* [HG100RL4SA-21] Add Colombia MTA Country Code : modify : 37-> 38 */
/* [HG100RL4GT-13] Add Guatemala MTA Country Code : modify 38 -> 39*/
/* [HG100RL4EC] Add Guatemala MTA Country Code : modify 39 -> 40*/
/* [HG100RL4GT-49] Add MTA Country Code : modify 40 -> 43*/
#define TOTAL_NUMBER_OF_LOCALE   43

typedef struct
{
   int   index;
   char  locale[3];
   char  vrgLocale[64];

} LOCALE_TABLE;

/* ---- Private Variables ------------------------------------------------ */
/* ---- Private Function Prototypes -------------------------------------- */
/* ---- Functions -------------------------------------------------------- */

static char BROADCOM_HEADER[] = \
"/****************************************************************************\n"\
"*\n"\
"*  Copyright ?2000-2007 Broadcom Corporation\n"\
"*\n"\
"*  This program is the proprietary software of Broadcom Corporation and/or\n"\
"*  its licensors, and may only be used, duplicated, modified or distributed\n"\
"*  pursuant to the terms and conditions of a separate, written license\n"\
"*  agreement executed between you and Broadcom (an \"Authorized License\").\n"\
"*  Except as set forth in an Authorized License, Broadcom grants no license\n"\
"*  (express or implied), right to use, or waiver of any kind with respect to\n"\
"*  the Software, and Broadcom expressly reserves all rights in and to the\n"\
"*  Software and all intellectual property rights therein.  IF YOU HAVE NO\n"\
"*  AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY,\n"\
"*  AND SHOULD IMMEDIATELY NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE\n"\
"*  SOFTWARE.  \n"\
"*\n"\
"*  Except as expressly set forth in the Authorized License,\n"\
"*\n"\
"*  1.     This program, including its structure, sequence and organization,\n"\
"*  constitutes the valuable trade secrets of Broadcom, and you shall use all\n"\
"*  reasonable efforts to protect the confidentiality thereof, and to use this\n"\
"*  information only in connection with your use of Broadcom integrated circuit\n"\
"*  products.\n"\
"*\n"\
"*  2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED\n"\
"*  \"AS IS\" AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS\n"\
"*  OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH\n"\
"*  RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL\n"\
"*  IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR\n"\
"*  A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET\n"\
"*  ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME\n"\
"*  THE ENTIRE RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE.\n"\
"*\n"\
"*  3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM\n"\
"*  OR ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL,\n"\
"*  INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY\n"\
"*  RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM\n"\
"*  HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN\n"\
"*  EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1,\n"\
"*  WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY\n"\
"*  FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.\n"\
"*\n"\
"****************************************************************************\n"\
"*\n" \
"*    Filename: vrgLocaleCfgGenerated.h\n" \
"*\n" \
"****************************************************************************\n" \
"*    Description:\n" \
"*\n" \
"*     Locale configuration file generated for this build.\n" \
"*\n" \
"*     THIS FILE IS AUTOMATICALLY GENERATED DURING BUILD, DO NOT EDIT.\n" \
"*\n" \
"****************************************************************************/\n";

/*
*****************************************************************************
** FUNCTION:   main
**
** PURPOSE:    Generates custom locale header file
**
** PARAMETERS: From command line, the first argument is meant to be
**             the path to store the generated file, the second 
**             argument is the locale list to use.
**
** RETURNS:    None
**
*****************************************************************************
*/
#ifdef WIN32
int _tmain(int argc, _TCHAR* argv[])
#else
int main( int argc, char **argv )
#endif
{
   FILE       *fd, *fd2;
   int        localeList[TOTAL_NUMBER_OF_LOCALE];
   int        localeIx, i, localeSet, firstLocale;
   char       localeFile[2048];

   // Define the locale currently supported.  Locale code are as per ISO-3166-1 code,
   // except for TR57 an ETSI, which are not defined under ISO-3166-1 country codes.
   //
   static LOCALE_TABLE localTable[] =
   {
      { 0, "us", "VRG_COUNTRY_CFG_NORTH_AMERICA" },   /* North America   */
      { 1, "jp", "VRG_COUNTRY_CFG_JAPAN" },         /* Japan         */
      { 2, "gb", "VRG_COUNTRY_CFG_UK" },            /* United Kingdom   */
      { 3, "se", "VRG_COUNTRY_CFG_SWEDEN" },         /* Sweden         */
      { 4, "de", "VRG_COUNTRY_CFG_GERMANY" },         /* Germany         */
      { 5, "fr", "VRG_COUNTRY_CFG_FRANCE" },         /* France         */
      { 6, "57", "VRG_COUNTRY_CFG_TR57" },             /* TR57            */
      { 7, "be", "VRG_COUNTRY_CFG_BELGIUM" },         /* Belgium         */
      { 8, "fi", "VRG_COUNTRY_CFG_FINLAND" },         /* Finland         */
      { 9, "it", "VRG_COUNTRY_CFG_ITALY" },         /* Italy         */
      { 10, "ei", "VRG_COUNTRY_CFG_ETSI" },         /* ETSI            */
      { 11, "nl", "VRG_COUNTRY_CFG_NETHERLANDS" },      /* Netherlands      */
      { 12, "ch", "VRG_COUNTRY_CFG_SWITZERLAND" },      /* Switzerland      */
      { 13, "br", "VRG_COUNTRY_CFG_BRAZIL" },         /* Brazil         */
      { 14, "dk", "VRG_COUNTRY_CFG_DENMARK" },         /* Denmark         */
      { 15, "hu", "VRG_COUNTRY_CFG_HUNGARY" },         /* Hungary         */
      { 16, "cl", "VRG_COUNTRY_CFG_CHILE" },         /* Chile         */
      { 17, "pl", "VRG_COUNTRY_CFG_POLAND" },         /* Poland         */
      { 18, "at", "VRG_COUNTRY_CFG_AUSTRIA" },         /* Austria         */
      { 19, "ie", "VRG_COUNTRY_CFG_IRELAND" },         /* Ireland         */
      { 20, "cz", "VRG_COUNTRY_CFG_CZECH" },         /* Czech Rep.      */
      { 21, "sk", "VRG_COUNTRY_CFG_SLOVAKIA" },      /* Slovakia         */
      { 22, "ro", "VRG_COUNTRY_CFG_ROMANIA" },         /* Romania         */
      { 23, "si", "VRG_COUNTRY_CFG_SLOVENIA" },      /* Slovenia         */
      { 24, "mx", "VRG_COUNTRY_CFG_MEXICO" },           /* Mexico         */
      { 25, "au", "VRG_COUNTRY_CFG_AUSTRALIA" },      /* Australia      */
      { 26, "sg", "VRG_COUNTRY_CFG_SINGAPORE" },      /* Singapore      */
      { 27, "tu", "VRG_COUNTRY_CFG_TURKEY" },      /* Turkey      */
      { 28, "cn", "VRG_COUNTRY_CFG_CHINA" },      /* China      */
      { 29, "no", "VRG_COUNTRY_CFG_NORWAY" },      /* Norway      */
      { 30, "in", "VRG_COUNTRY_CFG_INDIA" },      /* India         */
      { 31, "il", "VRG_COUNTRY_CFG_ISRAEL" },           /* Israel         */
      { 32, "nz", "VRG_COUNTRY_CFG_NEW_ZEALAND" },      /* New Zealand      */
      { 33, "es", "VRG_COUNTRY_CFG_SPAIN" },      /* Spain      */
      { 34, "tw", "VRG_COUNTRY_CFG_TAIWAN" },      /* Taiwan      */
      { 35, "ar", "VRG_COUNTRY_CFG_ARGENTINA" },      /* Argentina      */
      { 36, "ae", "VRG_COUNTRY_CFG_UAE" },      /* UAE      */
      { 37, "co", "VRG_COUNTRY_CFG_COLOMBIA" },         /* Colombial [HG100RL4SA-21] Add Colombia MTA Country Code */
      { 38, "gt", "VRG_COUNTRY_CFG_GUATEMALA" },       /* Guatemala [HG100RL4GT-13] Add Guatemala MTA Country Code */      
      { 39, "ec", "VRG_COUNTRY_CFG_ECUADOR" },       /* Ecuador [HG100RL4EC] Add Guatemala MTA Country Code */            
      { 40, "sv", "VRG_COUNTRY_CFG_ELSALVADOR" },         /* [HG100RL4GT-49] Add MTA Country Code */
      { 41, "hn", "VRG_COUNTRY_CFG_HONDURAS" },        
      { 42, "ni", "VRG_COUNTRY_CFG_NICARAGUA" },        
      { TOTAL_NUMBER_OF_LOCALE, "" },
   };

   // Parse the locale list to find out which countries need to be set.
   //
   for( localeIx = 0 ; localeIx < TOTAL_NUMBER_OF_LOCALE ; localeIx++ )
   {
      localeList[localeIx] = 0;
   }
   char *p = argv[2];
   char *q = NULL;
   char r;
   int parse = 1;
   int copyOver = 0;

   if( (argc != 3) || (strlen(p) == 0) )
   {
      parse = 0;
   }

   localeSet = 0;
   firstLocale = -1;

   while( parse )
   {
      // Get the next item in the list or up to the end of it.
      //
      if( (q = strchr( p, ',' )) == NULL )
      {
         // There will be no more item in the list.
         //
         parse = 0;
      }

      // Get the current item.
      //
      r = *(p + 2);    // All locale codes are two characters long per ISO-3361-1 definition.
      *(p + 2) = '\0';
      localeIx = TOTAL_NUMBER_OF_LOCALE;
      for( i = 0 ; i < TOTAL_NUMBER_OF_LOCALE ; i++ )
      {
         if( strcmp( localTable[i].locale, p ) == 0 )
         {
            localeIx = i;

            // determine if it's the first locale in the list
            if (firstLocale == -1)
            {
               // store country code of first locale
               firstLocale = localeIx;
            }
            break;
         }
      }
      if( localeIx != TOTAL_NUMBER_OF_LOCALE )
      {
         localeList[localeIx] = 1;
         localeSet++;
      }
      // Restore overwritten character. */
      *(p + 2) = r;
      p = q + 1;
   };

   // Now we have our list of locale set, create the configuration file.
   //
   chdir( argv[1] );
   fd = fopen( "vrgLocaleCfgGenerated.h.new", "w" );
   if( fd == NULL )
   {
      fprintf( stderr, "Failed to create the locale configuration file!" );
      return( -1 );
   }

   fprintf( fd, "%s\n", BROADCOM_HEADER );
   fprintf( fd, "#ifndef __VRG_LOCALE_CFG_GENERATED__INCLUDED__\n" );
   fprintf( fd, "#define __VRG_LOCALE_CFG_GENERATED__INCLUDED__\n\n\n" );

   // If at least one locale was set from this process, use the feature, otherwise do
   // not use it.
   //
   fprintf( fd, "#define VRG_COUNTRY_CFG_BUILD_GENERATED_INFO\t\t%d\n\n\n", (localeSet ? 1 : 0) );
   if( localeSet )
   {
      for( i = 0 ; i < TOTAL_NUMBER_OF_LOCALE ; i++ )
      {
         fprintf( fd, "#define %s\t\t%d\n", localTable[i].vrgLocale, localeList[i] );
      }
      // set the #define for the first country code in the list from build options first
      if (firstLocale != -1)
      {
         fprintf( fd, "#define %s\t\t%d\n", "VRG_COUNTRY_CFG_FIRST", localTable[firstLocale].index );
      }
   }
   fprintf( fd, "\n\n#endif /* __VRG_LOCALE_CFG_GENERATED__INCLUDED__ */\n" );
   fclose( fd );

   // Check whether or not the file already exists and if so whether this new one is different
   // or not before overwriting it ...
   //
   fd2 = fopen( "vrgLocaleCfgGenerated.h", "r" );
   if( fd2 != NULL )
   {
      int a1, a2;
      // A file already exists, we need to check if this is the same that would be generated
      // or not.  If same, do not change the current file so we do not incur build changes
      // for no reason.  If different, overwrite the old one with the new one.
      //
      fd = fopen( "vrgLocaleCfgGenerated.h.new", "r" );
      do
      {
         a1 = fgetc( fd );
         a2 = fgetc( fd2 );
      }
      while( ((a1 != EOF) || (a2 != EOF)) && (a1 == a2) );

      fclose( fd );
      fclose( fd2 );

      if( (a1 == EOF) && (a2 == EOF) )
      {
        // Files are identical in this case.  Do not do anything to replace them.
        //
        copyOver = 0;
      }
      else
      {
        copyOver = 1;
      }
   }
   else
   {
      copyOver = 1;
   }

   if( copyOver )
   {
      sprintf( localeFile, "cp vrgLocaleCfgGenerated.h.new vrgLocaleCfgGenerated.h" );
      system( localeFile );
   }

   // Remove temporary file.
   sprintf( localeFile, "rm vrgLocaleCfgGenerated.h.new" );
   system( localeFile );

   return ( 0 );
}

