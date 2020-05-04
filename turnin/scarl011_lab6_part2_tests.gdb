# Test file for "L6P1"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
test "after 1 sec go to s1"
# Set inputs
# Continue for several ticks
timeContinue 1
# Set expect values
expectPORTB 0x01
# Check pass/fail
checkResult

# Add tests below

test "t=2, val 2"
timeContinue 1
expectPORTB 0x02
checkResult

test " t=3, value = 4"
timeContinue 1
expectPORTB 0x04
checkResult

test "cycle please"
timeContinue 1
expectPORTB 0X01
checkResult

test "press button"
setPINA 0x01
timeContinue 3
expectPORTB 0x01
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
