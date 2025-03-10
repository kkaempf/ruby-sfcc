/*
 * Cim::Flags
 * 
 */

#include "cim_flags.h"

VALUE cSfccCimFlags;
void init_cim_flags(void)
{
  VALUE sfcc = rb_define_module("Sfcc");

  /**
   * data on the CIM namespace
   */
  VALUE klass = rb_define_class_under(sfcc, "Flags", rb_cObject);
  cSfccCimFlags = klass;

  rb_define_const(klass, "LocalOnly",          INT2FIX(CIMC_FLAG_LocalOnly));
  rb_define_const(klass, "DeepInheritance",    INT2FIX(CIMC_FLAG_DeepInheritance));
  rb_define_const(klass, "IncludeQualifiers",  INT2FIX(CIMC_FLAG_IncludeQualifiers));
  rb_define_const(klass, "IncludeClassOrigin", INT2FIX(CIMC_FLAG_IncludeClassOrigin));

}
