################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/nenad/workspace/personal/eclipse/neon/tests/test_nbits.c \
/home/nenad/workspace/personal/eclipse/neon/tests/test_nlist_dll.c \
/home/nenad/workspace/personal/eclipse/neon/tests/test_nlist_sll.c \
/home/nenad/workspace/personal/eclipse/neon/tests/test_nlqueue.c \
/home/nenad/workspace/personal/eclipse/neon/tests/test_nport.c 

OBJS += \
./tests/test_nbits.o \
./tests/test_nlist_dll.o \
./tests/test_nlist_sll.o \
./tests/test_nlqueue.o \
./tests/test_nport.o 

C_DEPS += \
./tests/test_nbits.d \
./tests/test_nlist_dll.d \
./tests/test_nlist_sll.d \
./tests/test_nlqueue.d \
./tests/test_nport.d 


# Each subdirectory must supply rules for building sources it contributes
tests/test_nbits.o: /home/nenad/workspace/personal/eclipse/neon/tests/test_nbits.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DNEON_TEST_NLQUEUE -I"/home/nenad/workspace/personal/eclipse/neon/lib" -I"/home/nenad/workspace/personal/eclipse/neon/variant/arch/x86" -I"/home/nenad/workspace/personal/eclipse/neon/variant/board/generic" -I"/home/nenad/workspace/personal/eclipse/neon/variant/mcu/generic" -I"/home/nenad/workspace/personal/eclipse/neon/variant/os/linux" -I"/home/nenad/workspace/personal/eclipse/neon/variant/platform/gcc" -I"/home/nenad/workspace/personal/eclipse/neon/testsuite" -I"/home/nenad/workspace/personal/eclipse/neon/tests" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

tests/test_nlist_dll.o: /home/nenad/workspace/personal/eclipse/neon/tests/test_nlist_dll.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DNEON_TEST_NLQUEUE -I"/home/nenad/workspace/personal/eclipse/neon/lib" -I"/home/nenad/workspace/personal/eclipse/neon/variant/arch/x86" -I"/home/nenad/workspace/personal/eclipse/neon/variant/board/generic" -I"/home/nenad/workspace/personal/eclipse/neon/variant/mcu/generic" -I"/home/nenad/workspace/personal/eclipse/neon/variant/os/linux" -I"/home/nenad/workspace/personal/eclipse/neon/variant/platform/gcc" -I"/home/nenad/workspace/personal/eclipse/neon/testsuite" -I"/home/nenad/workspace/personal/eclipse/neon/tests" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

tests/test_nlist_sll.o: /home/nenad/workspace/personal/eclipse/neon/tests/test_nlist_sll.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DNEON_TEST_NLQUEUE -I"/home/nenad/workspace/personal/eclipse/neon/lib" -I"/home/nenad/workspace/personal/eclipse/neon/variant/arch/x86" -I"/home/nenad/workspace/personal/eclipse/neon/variant/board/generic" -I"/home/nenad/workspace/personal/eclipse/neon/variant/mcu/generic" -I"/home/nenad/workspace/personal/eclipse/neon/variant/os/linux" -I"/home/nenad/workspace/personal/eclipse/neon/variant/platform/gcc" -I"/home/nenad/workspace/personal/eclipse/neon/testsuite" -I"/home/nenad/workspace/personal/eclipse/neon/tests" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

tests/test_nlqueue.o: /home/nenad/workspace/personal/eclipse/neon/tests/test_nlqueue.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DNEON_TEST_NLQUEUE -I"/home/nenad/workspace/personal/eclipse/neon/lib" -I"/home/nenad/workspace/personal/eclipse/neon/variant/arch/x86" -I"/home/nenad/workspace/personal/eclipse/neon/variant/board/generic" -I"/home/nenad/workspace/personal/eclipse/neon/variant/mcu/generic" -I"/home/nenad/workspace/personal/eclipse/neon/variant/os/linux" -I"/home/nenad/workspace/personal/eclipse/neon/variant/platform/gcc" -I"/home/nenad/workspace/personal/eclipse/neon/testsuite" -I"/home/nenad/workspace/personal/eclipse/neon/tests" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

tests/test_nport.o: /home/nenad/workspace/personal/eclipse/neon/tests/test_nport.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DNEON_TEST_NLQUEUE -I"/home/nenad/workspace/personal/eclipse/neon/lib" -I"/home/nenad/workspace/personal/eclipse/neon/variant/arch/x86" -I"/home/nenad/workspace/personal/eclipse/neon/variant/board/generic" -I"/home/nenad/workspace/personal/eclipse/neon/variant/mcu/generic" -I"/home/nenad/workspace/personal/eclipse/neon/variant/os/linux" -I"/home/nenad/workspace/personal/eclipse/neon/variant/platform/gcc" -I"/home/nenad/workspace/personal/eclipse/neon/testsuite" -I"/home/nenad/workspace/personal/eclipse/neon/tests" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


