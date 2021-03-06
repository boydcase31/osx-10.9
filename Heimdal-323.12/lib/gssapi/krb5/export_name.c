/*
 * Copyright (c) 1997, 1999, 2003 Kungliga Tekniska Högskolan
 * (Royal Institute of Technology, Stockholm, Sweden).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "gsskrb5_locl.h"

static OM_uint32
export_name_common(OM_uint32  *minor_status,
		   gss_const_OID oid,
		   const gss_name_t input_name,
		   gss_buffer_t exported_name)
{
    krb5_const_principal princ = (krb5_const_principal)input_name;
    krb5_error_code ret;
    krb5_context context;
    OM_uint32 major_status;
    char *name;
    
    GSSAPI_KRB5_INIT (&context);
    
    ret = krb5_unparse_name (context, princ, &name);
    if (ret) {
	*minor_status = ret;
	return GSS_S_FAILURE;
    }
    
    major_status = gss_mg_export_name(minor_status, oid, 
				      name, strlen(name),
				      exported_name);
    krb5_xfree(name);
    return major_status;
    
}

OM_uint32
_gsskrb5_export_name(OM_uint32  * minor_status,
		     const gss_name_t input_name,
		     gss_buffer_t exported_name)
{
    return export_name_common(minor_status, GSS_KRB5_MECHANISM, input_name, exported_name);
}

OM_uint32
_gsspku2u_export_name(OM_uint32  * minor_status,
		      const gss_name_t input_name,
		      gss_buffer_t exported_name)
{
    return export_name_common(minor_status, GSS_PKU2U_MECHANISM, input_name, exported_name);
}

OM_uint32
_gssiakerb_export_name(OM_uint32  * minor_status,
		      const gss_name_t input_name,
		      gss_buffer_t exported_name)
{
    return export_name_common(minor_status, GSS_KRB5_MECHANISM, input_name, exported_name);
}
