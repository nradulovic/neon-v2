################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main.c 

OBJS += \
./main.o 

C_DEPS += \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DNEON_TEST_NLQUEUE -I"/home/nenad/workspace/personal/eclipse/neon/lib" -I"/home/nenad/workspace/personal/eclipse/neon/variant/arch/x86" -I"/home/nenad/workspace/personal/eclipse/neon/variant/board/generic" -I"/home/nenad/workspace/personal/eclipse/neon/variant/mcu/generic" -I"/home/nenad/workspace/personal/eclipse/neon/variant/os/linux" -I"/home/nenad/workspace/personal/eclipse/neon/variant/platform/gcc" -I"/home/nenad/workspace/personal/eclipse/neon/testsuite" -I"/home/nenad/workspace/personal/eclipse/neon/tests" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


