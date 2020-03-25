################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
DSP2833x_common/source/%.obj: ../DSP2833x_common/source/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/opt/ti/ccs1000/ccs/tools/compiler/ti-cgt-c2000_20.2.0.LTS/bin/cl2000" -v28 -ml -mt --include_path="D:/Workspace/CCS_V10/S04_AS608_FINGERPRINT_F28335_CCS10" --include_path="../DSP2833x_common/include" --include_path="../DSP2833x_headers/include" --include_path="../inc" --include_path="C:/opt/ti/ccs1000/ccs/tools/compiler/ti-cgt-c2000_20.2.0.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="DSP2833x_common/source/$(basename $(<F)).d_raw" --obj_directory="DSP2833x_common/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

DSP2833x_common/source/%.obj: ../DSP2833x_common/source/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/opt/ti/ccs1000/ccs/tools/compiler/ti-cgt-c2000_20.2.0.LTS/bin/cl2000" -v28 -ml -mt --include_path="D:/Workspace/CCS_V10/S04_AS608_FINGERPRINT_F28335_CCS10" --include_path="../DSP2833x_common/include" --include_path="../DSP2833x_headers/include" --include_path="../inc" --include_path="C:/opt/ti/ccs1000/ccs/tools/compiler/ti-cgt-c2000_20.2.0.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="DSP2833x_common/source/$(basename $(<F)).d_raw" --obj_directory="DSP2833x_common/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


