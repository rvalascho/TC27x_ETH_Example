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
# Subdirectory make file for 0_Src/AppSw/lwip/src/core/ipv6
# !! Generated make file, modifications could be overwritten !!
#------------------------------------------------------------------------------


# Make-Rules:
# Make-rules for architecture: Tricore

#Make-rule to build file: dhcp6.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/dhcp6.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/dhcp6.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/dhcp6.o: 0_Src/AppSw/lwip/src/core/ipv6/dhcp6.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file dhcp6.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: ethip6.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/ethip6.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/ethip6.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/ethip6.o: 0_Src/AppSw/lwip/src/core/ipv6/ethip6.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file ethip6.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: icmp6.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/icmp6.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/icmp6.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/icmp6.o: 0_Src/AppSw/lwip/src/core/ipv6/icmp6.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file icmp6.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: inet6.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/inet6.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/inet6.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/inet6.o: 0_Src/AppSw/lwip/src/core/ipv6/inet6.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file inet6.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: ip6.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/ip6.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/ip6.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/ip6.o: 0_Src/AppSw/lwip/src/core/ipv6/ip6.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file ip6.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: ip6_addr.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/ip6_addr.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/ip6_addr.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/ip6_addr.o: 0_Src/AppSw/lwip/src/core/ipv6/ip6_addr.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file ip6_addr.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: ip6_frag.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/ip6_frag.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/ip6_frag.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/ip6_frag.o: 0_Src/AppSw/lwip/src/core/ipv6/ip6_frag.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file ip6_frag.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: mld6.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/mld6.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/mld6.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/mld6.o: 0_Src/AppSw/lwip/src/core/ipv6/mld6.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file mld6.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: nd6.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/nd6.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/nd6.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ipv6/nd6.o: 0_Src/AppSw/lwip/src/core/ipv6/nd6.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file nd6.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)
