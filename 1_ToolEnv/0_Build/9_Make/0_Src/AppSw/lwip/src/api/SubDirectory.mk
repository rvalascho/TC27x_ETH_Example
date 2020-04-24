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
# Subdirectory make file for 0_Src/AppSw/lwip/src/api
# !! Generated make file, modifications could be overwritten !!
#------------------------------------------------------------------------------


# Make-Rules:
# Make-rules for architecture: Tricore

#Make-rule to build file: api_lib.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/api_lib.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/api_lib.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/api_lib.o: 0_Src/AppSw/lwip/src/api/api_lib.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file api_lib.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: api_msg.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/api_msg.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/api_msg.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/api_msg.o: 0_Src/AppSw/lwip/src/api/api_msg.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file api_msg.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: err.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/err.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/err.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/err.o: 0_Src/AppSw/lwip/src/api/err.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file err.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: netbuf.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/netbuf.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/netbuf.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/netbuf.o: 0_Src/AppSw/lwip/src/api/netbuf.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file netbuf.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: netdb.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/netdb.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/netdb.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/netdb.o: 0_Src/AppSw/lwip/src/api/netdb.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file netdb.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: netifapi.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/netifapi.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/netifapi.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/netifapi.o: 0_Src/AppSw/lwip/src/api/netifapi.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file netifapi.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: sockets.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/sockets.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/sockets.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/sockets.o: 0_Src/AppSw/lwip/src/api/sockets.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file sockets.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)

#Make-rule to build file: tcpip.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/tcpip.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/tcpip.o

2_Out/Tricore_Tasking/Tasking_Files/0_Src/AppSw/lwip/src/api/tcpip.o: 0_Src/AppSw/lwip/src/api/tcpip.c $(B_GEN_CONFIG_TRICORE_TASKING)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file tcpip.c for Tricore'
	$(B_GEN_TRICORE_TASKING_CC) -f $(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -o $(@:.o=.src) $< --dep-file=$(@:.o=.dep) $(B_TASKING_TRICORE_CC_OPTIONS)
	$(B_GEN_TRICORE_TASKING_AS1) -o $@ $(@:.o=.src) $(B_TASKING_TRICORE_ASM_OPTIONS)
	$(B_GEN_TRICORE_TASKING_DEPCONV) -e 's/\($(subst .,\.,$(@F)) *:\)/$(subst /,\/,$(@D))\/\1/g' -e 's/\\/\//g' -e '/\"/d' $(@:.o=.dep) > $(@:.o=.d) ; rm -f $(@:.o=.dep)
