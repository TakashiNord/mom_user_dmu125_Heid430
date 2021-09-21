//////////////////////////////////////////////////////////////////////////////
//
//  mom_user.cpp
//
//  Description:
//      Contains Unigraphics entry points for the application.
//
//////////////////////////////////////////////////////////////////////////////

// #define _CRT_SECURE_NO_DEPRECATE 1

//  Include files
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <uf.h>
#include <uf_exit.h>
#include <uf_ui.h>
#include <uf_mom.h>

#include <windows.h>

#include "mom_user.h"

//----------------------------------------------------------------------------

/*
 * Çàùèòà ÷åðåç íîìåð òîìà:
 */
int sub_10001720() ;
/*
 * Exported Tcl procedures:
 */
static int sub_10001080
(
  void *client_data,    /* This is the mom object */
  void *interp,         /* Pointer to the TCL interpreter */
  int  argc,            /* Count of the numnber of arguments */
  char **argv           /* Array of arguments where the
                           argv[0] - The TCL extension */
);

//----------------------------------------------------------------------------
//  Activation Methods
//----------------------------------------------------------------------------

//  Explicit Activation
//      This entry point is used to activate the application explicitly, as in
//      "File->Execute UG/Open->User Function..."
//----- (10001010) --------------------------------------------------------
extern "C" DllExport void entry_rtv_mom_cp_part_attr( char *parm, int *returnCode, int rlen )
{
  int errorCode ;
  UF_MOM_id_t mom ;
  void *interp = NULL ;

  if ( !UF_is_initialized() )
  {
    errorCode = UF_initialize();
	*returnCode = errorCode;
    if ( errorCode ) return ;
  }

  /* Get the TCL interpreter id from the ufusr param */
  UF_MOM_ask_interp_from_param ( parm, &interp ) ;
  /* Get the MOM id from the ufusr param */
  UF_MOM_ask_mom (parm, &mom) ;
  /*Ñîçäàåì ôóíêöèè â èíòåïðåòàòîðå*/
  UF_MOM_extend_xlator ( mom , "EXTN_rtv_mom_cp_part_attr", sub_10001080 ) ;

  *returnCode = 0;
  if ( errorCode == 1 )  errorCode = UF_terminate();
  *returnCode = errorCode;
}


//----------------------------------------------------------------------------
//  Utilities
//----------------------------------------------------------------------------

// Unload Handler
//     This function specifies when to unload your application from Unigraphics.
//     If your application registers a callback (from a MenuScript item or a
//     User Defined Object for example), this function MUST return
//     "UF_UNLOAD_UG_TERMINATE".
extern "C" int ufusr_ask_unload( void )
{
     /* unload immediately after application exits*/
     //return ( UF_UNLOAD_IMMEDIATELY );

     /*via the unload selection dialog... */
     //return ( UF_UNLOAD_SEL_DIALOG );
     /*when UG terminates...              */
     return ( UF_UNLOAD_UG_TERMINATE );
}


/*-----------------------------------------------------------------------
 * Function Name: sub_10001080
 *
 *
 -----------------------------------------------------------------------*/
static int sub_10001080
(
  void *client_data,    /* This is the mom object */
  void *interp,         /* Pointer to the TCL interpreter */
  int  argc,            /* Count of the numnber of arguments */
  char **argv           /* Array of arguments where the
                           argv[0] - The TCL extension */
)
{
  UF_MOM_id_t mom_id = ( UF_MOM_id_t ) client_data ;

  int     ii ;
  char    Dest[256] ;
  double  angle1 , angle2 ;
  double  x , y , z , i , j , k ;

  int  dword_10003334 = 0 ;

  if ( sub_10001720() == 0 )
  {
	const int Size = 1024 ;
    char  str[Size]="ÍÀ ÝÒÎÌ ÐÀÁÎ×ÅÌ ÌÅÑÒÅ ÏÎÑÒÏÐÎÖÅÑÑÎÐ ÍÅ ÌÎÆÅÒ ÁÛÒÜ ÇÀÏÓÙÅÍ\n \
Ìîñêâà, CSoft (ÇÀÎ \"ÑèÑîôò\"),\nÒåëåôîí: +7 (495) 913-22-22, Ôàêñ: +7 (495) 913-22-21\n \
e-mail: jura@csoft.ru, g00@inbox.ru\nHTTP: http://www.csoft.ru\n\n(c) 2007.\n\n\nÏîñëåäíÿÿ ðåäàêöèÿ èþëü 2007\0";

    UF_UI_display_nonmodal_msg("Âíèìàíèå!", str, UF_UI_MSG_POS_CURSOR);
    UF_terminate();
    return ( 0 ) ;
  }

    sprintf(Dest, "Number of args %ld", argc);
    if ( argc > 0 )
    {
      for (ii=0;ii<argc;ii++) sprintf(Dest, "Arg 0 %s", argv[ii]);
    }

   	if (0==strcmp(argv[1],"PLANE"))
   	{
      UF_MOM_ask_assoc_double_array(mom_id, "out_angle_pos", "0", &angle1);
      UF_MOM_ask_assoc_double_array(mom_id, "out_angle_pos", "1", &angle2);
      sprintf(Dest, "MOM_output_literal \"CYCL DEF 19.0 WORKING PLANE\"");
      UF_MOM_execute_command(mom_id, Dest);
      sprintf(Dest, "MOM_output_literal \"CYCL DEF 19.1 B%.3lf C%.3lf F1000 \"", angle1, angle2);
      UF_MOM_execute_command(mom_id, Dest);
      sprintf(Dest, "MOM_output_literal \"L C+Q122 B+Q121 R0 F MAX\"");
      UF_MOM_execute_command(mom_id, Dest);	  
   	}

   	if (0==strcmp(argv[1],"PLANE_moving"))
   	{
      UF_MOM_ask_assoc_double_array(mom_id, "mcs_goto", "0", &x);
      UF_MOM_ask_assoc_double_array(mom_id, "mcs_goto", "1", &y);
      UF_MOM_ask_assoc_double_array(mom_id, "mcs_goto", "2", &z);
      sprintf(Dest, "MOM_output_literal \"L X%.3lf Y%.3lf F MAX\"", x, y);
      UF_MOM_execute_command(mom_id, Dest);
      sprintf(Dest, "MOM_output_literal \"L Z%.3lf F MAX\"", z);
	  UF_MOM_execute_command(mom_id, Dest);
   	}	

   	if (0==strcmp(argv[1],"PLANE_moving_rot"))
   	{
      UF_MOM_ask_assoc_double_array(mom_id, "pos", "0", &x);
      UF_MOM_ask_assoc_double_array(mom_id, "pos", "1", &y);
      UF_MOM_ask_assoc_double_array(mom_id, "pos", "2", &z);
      sprintf(Dest, "MOM_output_literal \"L X%.3lf Y%.3lf F MAX\"", x, y);
      UF_MOM_execute_command(mom_id, Dest);
      sprintf(Dest, "MOM_output_literal \"L Z%.3lf F MAX\"", z);
	  UF_MOM_execute_command(mom_id, Dest);
   	}	
	
	if ( !strcmp(argv[1], "M128") )
    {
      UF_MOM_ask_assoc_double_array(mom_id, "mcs_goto", "0", &x);
      UF_MOM_ask_assoc_double_array(mom_id, "mcs_goto", "1", &y);
      UF_MOM_ask_assoc_double_array(mom_id, "mcs_goto", "2", &z);
      UF_MOM_set_assoc_double_array(mom_id, "pos", "0", x);
      UF_MOM_set_assoc_double_array(mom_id, "pos", "1", y);
      UF_MOM_set_assoc_double_array(mom_id, "pos", "2", z);
    }

	if ( !strcmp(argv[1], "M128_init") )
    {
      i = 0 ;
	  j = 1719609481 ;
	  k = 1719609481 ;
	  UF_MOM_set_assoc_double_array(mom_id, "kin_4th_axis_vector", "0", i);
      UF_MOM_set_assoc_double_array(mom_id, "kin_4th_axis_vector", "1", j);
      UF_MOM_set_assoc_double_array(mom_id, "kin_4th_axis_vector", "2", k);
      sprintf(Dest, "MOM_reload_kinematics");
      UF_MOM_execute_command(mom_id, Dest);
    }
	
   	if (0==strcmp(argv[1],"M128_init_zero"))
   	{
      UF_MOM_ask_assoc_double_array(mom_id, "kin_4th_axis_vector", "0", &i);
      UF_MOM_ask_assoc_double_array(mom_id, "kin_4th_axis_vector", "1", &j);
      UF_MOM_ask_assoc_double_array(mom_id, "kin_4th_axis_vector", "2", &k);
      i = 0 ;
      j = 0 ;
      k = 0 ;
	  UF_MOM_set_assoc_double_array(mom_id, "kin_4th_axis_vector", "0", i);
      UF_MOM_set_assoc_double_array(mom_id, "kin_4th_axis_vector", "1", j);
      UF_MOM_set_assoc_double_array(mom_id, "kin_4th_axis_vector", "2", k);
   	}

    if ( !strcmp(argv[1], "UNLOAD") ) dword_10003334 = 0;
    UF_MOM_set_string(mom_id, "var_unknow", Dest);
    UF_terminate();	
	
  return ( 0 ) ;
}

//----- (sub_10001720) --------------------------------------------------------
int sub_10001720()
{
  char VolumeNameBuffer[MAX_PATH]; // [sp+444h] [bp-3E8h]@1
  DWORD VolumeSerialNumber; // [sp+0h] [bp-82Ch]@1
  DWORD MaximumComponentLength; // [sp+54h] [bp-7D8h]@1
  DWORD FileSystemFlags; // [sp+58h] [bp-7D4h]@1
  char FileSystemNameBuffer[MAX_PATH]; // [sp+5Ch] [bp-7D0h]@1

  int i ;
  static DWORD sp[]=
  {  0x0BCEC3EDA , 0x1C6992FB , 0x9C21B9ED , 0x0C4DF5004 , 0x0A0FA9C41 , 0x28F9C2CB , 0x68D16F49 , 0x48CA45A7 ,
	 0x2020D423 , 0x0C0D78CB1 , 0x964961F2 ,
     1 } ;

  GetVolumeInformation(
    "C:\\",
    VolumeNameBuffer,
    sizeof(VolumeNameBuffer),
    &VolumeSerialNumber,
    &MaximumComponentLength,
    &FileSystemFlags,
    FileSystemNameBuffer,
    sizeof(FileSystemNameBuffer));

  i = 0;
  while ( VolumeSerialNumber != sp[i] )
  {
    ++i;
    if ( i >= 12 ) return 0;
  }
  return 1;
}