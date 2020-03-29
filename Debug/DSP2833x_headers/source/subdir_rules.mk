################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
DSP2833x_headers/source/DSP2833x_GlobalVariableDefs.obj: ../DSP2833x_headers/source/DSP2833x_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_20.2.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="D:/Workspace/CCS_V8/S04-AS608-FINGER-F28335-CCSV8" --include_path="../DSP2833x_common/include" --include_path="../DSP2833x_headers/include" --include_path="../inc" --include_path="C:/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_20.2.0.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="DSP2833x_headers/source/DSP2833x_GlobalVariableDefs.d_raw" --obj_directory="DSP2833x_headers/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


