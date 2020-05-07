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
test "after 1 tick  go to s0"
# Set inputs
# Continue for several ticks
timeContinue 1
# Set expect values
expectPORTB 0x07
# Check pass/fail
checkResult

# Add tests below

test "pina = 1; val 2"
setPINA ~0x01
timeContinue 4
expectPORTB 0x08
checkResult

test "time continue 4 value = 9"
timeContinue 10
expectPORTB 0x09
checkResult

test "t=6, val 6"
setPINA ~0x00
timeContinue 10
setPINA ~0x02
timeContinue 40
expectPORTB 0X04
checkResult

test "press buttons"
setPINA ~0x03
timeContinue 3
expectPORTB 0x00
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
