################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/as608.obj: ../src/as608.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_20.2.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="D:/Workspace/CCS_V8/S04-AS608-FINGER-F28335-CCSV8" --include_path="../DSP2833x_common/include" --include_path="../DSP2833x_headers/include" --include_path="../inc" --include_path="C:/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_20.2.0.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="src/as608.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/main.obj: ../src/main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_20.2.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="D:/Workspace/CCS_V8/S04-AS608-FINGER-F28335-CCSV8" --include_path="../DSP2833x_common/include" --include_path="../DSP2833x_headers/include" --include_path="../inc" --include_path="C:/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_20.2.0.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="src/main.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/sci.obj: ../src/sci.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_20.2.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="D:/Workspace/CCS_V8/S04-AS608-FINGER-F28335-CCSV8" --include_path="../DSP2833x_common/include" --include_path="../DSP2833x_headers/include" --include_path="../inc" --include_path="C:/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_20.2.0.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="src/sci.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


