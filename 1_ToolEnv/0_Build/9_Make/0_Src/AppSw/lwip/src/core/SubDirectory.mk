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
# Subdirectory make file for 0_Src/AppSw/lwip/src/core
# !! Generated make file, modifications could be overwritten !!
#------------------------------------------------------------------------------


# Include sub folder make files
include 1_ToolEnv/0_Build/9_Make/0_Src/AppSw/lwip/src/core/ipv4/SubDirectory.mk
include 1_ToolEnv/0_Build/9_Make/0_Src/AppSw/lwip/src/core/ipv6/SubDirectory.mk

# Make-Rules:
# Make-rules for architecture: Tricore

#Make-rule to build file: def.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/def.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/def.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/def.o: 0_Src/AppSw/lwip/src/core/def.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file def.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: dns.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/dns.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/dns.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/dns.o: 0_Src/AppSw/lwip/src/core/dns.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file dns.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: inet_chksum.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/inet_chksum.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/inet_chksum.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/inet_chksum.o: 0_Src/AppSw/lwip/src/core/inet_chksum.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file inet_chksum.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: init.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/init.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/init.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/init.o: 0_Src/AppSw/lwip/src/core/init.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file init.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: ip.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ip.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ip.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/ip.o: 0_Src/AppSw/lwip/src/core/ip.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file ip.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: mem.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/mem.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/mem.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/mem.o: 0_Src/AppSw/lwip/src/core/mem.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file mem.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: memp.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/memp.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/memp.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/memp.o: 0_Src/AppSw/lwip/src/core/memp.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file memp.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: netif.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/netif.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/netif.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/netif.o: 0_Src/AppSw/lwip/src/core/netif.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file netif.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: pbuf.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/pbuf.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/pbuf.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/pbuf.o: 0_Src/AppSw/lwip/src/core/pbuf.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file pbuf.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: raw.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/raw.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/raw.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/raw.o: 0_Src/AppSw/lwip/src/core/raw.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file raw.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: stats.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/stats.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/stats.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/stats.o: 0_Src/AppSw/lwip/src/core/stats.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file stats.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: sys.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/sys.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/sys.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/sys.o: 0_Src/AppSw/lwip/src/core/sys.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file sys.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: tcp.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/tcp.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/tcp.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/tcp.o: 0_Src/AppSw/lwip/src/core/tcp.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file tcp.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: tcp_in.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/tcp_in.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/tcp_in.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/tcp_in.o: 0_Src/AppSw/lwip/src/core/tcp_in.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file tcp_in.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: tcp_out.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/tcp_out.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/tcp_out.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/tcp_out.o: 0_Src/AppSw/lwip/src/core/tcp_out.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file tcp_out.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: timeouts.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/timeouts.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/timeouts.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/timeouts.o: 0_Src/AppSw/lwip/src/core/timeouts.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file timeouts.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: udp.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/udp.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/udp.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/core/udp.o: 0_Src/AppSw/lwip/src/core/udp.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file udp.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)
