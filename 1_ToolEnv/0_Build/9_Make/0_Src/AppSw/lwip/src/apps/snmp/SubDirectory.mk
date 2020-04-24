# -----------------------------------------------------------------------------
#
# Copyright (C) 2015-2017 Infineon Technologies AG. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# - Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
# - Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation.
#   and/or other materials provided with the distribution.
# - Neither the name of the copyright holders nor the names of its
#   contributors may be used to endorse or promote products derived from this
#   software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# To improve the quality of the software, users are encouraged to share
# modifications, enhancements or bug fixes with Infineon Technologies AG
# (support@infineon.com).
# 
# -----------------------------------------------------------------------------
# Subdirectory make file for 0_Src/AppSw/lwip/src/apps/snmp
# !! Generated make file, modifications could be overwritten !!
#------------------------------------------------------------------------------


# Make-Rules:
# Make-rules for architecture: Tricore

#Make-rule to build file: snmpv3.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmpv3.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmpv3.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmpv3.o: 0_Src/AppSw/lwip/src/apps/snmp/snmpv3.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmpv3.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmpv3_dummy.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmpv3_dummy.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmpv3_dummy.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmpv3_dummy.o: 0_Src/AppSw/lwip/src/apps/snmp/snmpv3_dummy.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmpv3_dummy.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmpv3_mbedtls.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmpv3_mbedtls.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmpv3_mbedtls.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmpv3_mbedtls.o: 0_Src/AppSw/lwip/src/apps/snmp/snmpv3_mbedtls.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmpv3_mbedtls.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_asn1.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_asn1.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_asn1.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_asn1.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_asn1.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_asn1.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_core.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_core.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_core.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_core.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_core.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_core.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_mib2.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_mib2.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_mib2_icmp.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_icmp.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_icmp.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_icmp.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_icmp.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_mib2_icmp.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_mib2_interfaces.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_interfaces.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_interfaces.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_interfaces.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_interfaces.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_mib2_interfaces.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_mib2_ip.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_ip.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_ip.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_ip.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_ip.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_mib2_ip.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_mib2_snmp.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_snmp.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_snmp.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_snmp.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_snmp.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_mib2_snmp.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_mib2_system.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_system.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_system.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_system.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_system.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_mib2_system.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_mib2_tcp.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_tcp.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_tcp.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_tcp.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_tcp.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_mib2_tcp.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_mib2_udp.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_udp.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_udp.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_udp.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_mib2_udp.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_mib2_udp.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_msg.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_msg.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_msg.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_msg.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_msg.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_msg.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_netconn.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_netconn.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_netconn.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_netconn.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_netconn.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_netconn.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_pbuf_stream.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_pbuf_stream.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_pbuf_stream.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_pbuf_stream.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_pbuf_stream.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_pbuf_stream.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_raw.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_raw.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_raw.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_raw.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_raw.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_raw.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_scalar.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_scalar.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_scalar.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_scalar.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_scalar.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_scalar.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_table.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_table.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_table.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_table.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_table.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_table.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_threadsync.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_threadsync.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_threadsync.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_threadsync.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_threadsync.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_threadsync.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: snmp_traps.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_traps.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_traps.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/apps/snmp/snmp_traps.o: 0_Src/AppSw/lwip/src/apps/snmp/snmp_traps.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file snmp_traps.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)
