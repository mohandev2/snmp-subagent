##################################################
#
#  OpenHPI Macros
#
#  Copyright (C) IBM Corp 2005
#
#  Author(s):
#      Sean Dague <http://dague.net/sean>
#
#  This file is licensed under the same terms as OpenHPI itself.
#  See the COPYING file in the top level of OpenHPI for more info.
#
# This is a set of common macros to be used by the top
# level configure.in.
#
##################################################

#
# OH_CHECK_FAIL($LIBNAME,$PACKAGE_SUGGEST,$URL,$EXTRA)
#

AC_DEFUN(OH_CHECK_FAIL,
    [
    OH_MSG=`echo -e "- $1 not found!\n"`
    if test "x" != "x$4"; then
        OH_MSG=`echo -e "$OH_MSG\n- $4"`
    fi
    if test "x$2" != "x"; then
        OH_MSG=`echo -e "$OH_MSG\n- Try installing the $2 package\n"`
    fi
    if test "x$3" != "x"; then
        OH_MSG=`echo -e "$OH_MSG\n- or get the latest software from $3\n"`
    fi
    
    AC_MSG_ERROR(
!
************************************************************
$OH_MSG
************************************************************
)
    ]
)

AC_DEFUN(OH_CHECK_NETSNMP,
    [
    AC_MSG_CHECKING(for net-snmp)
    AC_TRY_LINK(
    [
        #include <net-snmp/net-snmp-config.h>
        #include <net-snmp/net-snmp-includes.h>
    ],
    [
        struct snmp_session session
    ],
    [
        have_netsnmp=yes
        SNMPFLAGS=`net-snmp-config --cflags`
        SNMPALIBS=`net-snmp-config --agent-libs`
	SNMPVERSIONOK=`net-snmp-config --version | awk -F\. '{ \
			if ( $[1] >= 5 ) { \
  				if ( $[2] > 0 ) print "OK"; \
 			if ( $[2] == 0) { \
   				if ( $[3] >= 8) print "OK"; \
 			} \
		} \
	}'`
        # the following seems to work... thankfully.
        SNMPCONFDIR=`net-snmp-config --configure-options | perl -p -e 's/.*sysconfdir=([\/\w]+).*/\1/'`
	if test "$SNMPVERSIONOK" == "OK"; then
	        AC_MSG_RESULT(yes)
	else
		AC_MSG_ERROR(no. Need NetSNMP version 5.0.7 or higher.)
	fi
    ],
    [AC_MSG_ERROR(no. NetSNMP is not found.!)])
])
