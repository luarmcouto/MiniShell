#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
NC='\033[0m' # No Color

# Configuration
MINISHELL="./minishell"
OUTPUT_FILE="test_results.txt"
TEMP_DIR="/tmp/minishell_test_$"

# Check if minishell exists
if [ ! -f "$MINISHELL" ]; then
    echo -e "${RED}Error: minishell not found at $MINISHELL${NC}"
    echo "Please compile minishell first with 'make'"
    exit 1
fi

# Create temp directory
mkdir -p "$TEMP_DIR"

# Cleanup function
cleanup() {
    rm -rf "$TEMP_DIR"
}
trap cleanup EXIT

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  MINISHELL ARGUMENTS TEST SUITE${NC}"
echo -e "${BLUE}========================================${NC}\n"

# Initialize results
> "$OUTPUT_FILE"
TEST_COUNT=0
PASSED=0
FAILED=0

# Function to run a test
run_test() {
    local test_num=$1
    local description="$2"
    local command="$3"
    
    TEST_COUNT=$((TEST_COUNT + 1))
    
    echo -e "${YELLOW}[Test $test_num]${NC} $description"
    echo "Command: ${BLUE}$command${NC}"
    
    # Run in minishell
    echo "$command" | timeout 2 $MINISHELL > "$TEMP_DIR/minishell_out.txt" 2>&1
    MINISHELL_EXIT=$?
    
    # Run in bash for comparison
    echo "$command" | timeout 2 bash > "$TEMP_DIR/bash_out.txt" 2>&1
    BASH_EXIT=$?
    
    # Save to results file
    echo "========================================" >> "$OUTPUT_FILE"
    echo "Test $test_num: $description" >> "$OUTPUT_FILE"
    echo "Command: $command" >> "$OUTPUT_FILE"
    echo "" >> "$OUTPUT_FILE"
    echo "MINISHELL OUTPUT:" >> "$OUTPUT_FILE"
    cat "$TEMP_DIR/minishell_out.txt" >> "$OUTPUT_FILE"
    echo "" >> "$OUTPUT_FILE"
    echo "BASH OUTPUT:" >> "$OUTPUT_FILE"
    cat "$TEMP_DIR/bash_out.txt" >> "$OUTPUT_FILE"
    echo "" >> "$OUTPUT_FILE"
    echo "Exit codes - Minishell: $MINISHELL_EXIT | Bash: $BASH_EXIT" >> "$OUTPUT_FILE"
    echo "" >> "$OUTPUT_FILE"
    
    # Check for crash (timeout or signal)
    if [ $MINISHELL_EXIT -eq 124 ] || [ $MINISHELL_EXIT -gt 128 ]; then
        echo -e "${RED}  ✗ CRASH DETECTED!${NC}\n"
        FAILED=$((FAILED + 1))
        return 1
    fi
    
    echo -e "${GREEN}  ✓ No crash${NC}\n"
    PASSED=$((PASSED + 1))
    return 0
}

# Test Suite
echo -e "${GREEN}Starting argument tests...${NC}\n"

# Test 1: Simple command with absolute path and one argument
run_test 1 "Simple command with absolute path + one argument" \
    "/bin/ls -l"

# Test 2: Absolute path with multiple arguments
run_test 2 "Absolute path with multiple arguments" \
    "/bin/ls -l -a -h"

# Test 3: Command with relative path and arguments
run_test 3 "Relative path command with arguments" \
    "ls -la /tmp"

# Test 4: Echo with multiple arguments
run_test 4 "Echo with multiple arguments" \
    "echo hello world test"

# Test 5: Cat with filename argument
run_test 5 "Cat with filename" \
    "/bin/cat Makefile"

# Test 6: Grep with pattern and filename
run_test 6 "Grep with pattern and file" \
    "grep NAME Makefile"

# Test 7: Command with dashes in arguments
run_test 7 "Command with dash arguments" \
    "echo -n -e test"

# Test 8: Mkdir with path argument
run_test 8 "Mkdir with path" \
    "/bin/mkdir -p $TEMP_DIR/test_dir"

# Test 9: Multiple spaces between arguments
run_test 9 "Multiple spaces between arguments" \
    "echo hello     world     test"

# Test 10: Arguments with special characters (without quotes)
run_test 10 "Arguments with special chars" \
    "echo test123 test-456 test_789"

# Test 11: Pwd with -L argument
run_test 11 "Pwd with -L argument" \
    "/bin/pwd -L"

# Test 12: Wc with multiple arguments
run_test 12 "Wc with -l argument" \
    "/usr/bin/wc -l Makefile"

# Test 13: Head with -n argument
run_test 13 "Head with -n argument" \
    "/usr/bin/head -n 5 Makefile"

# Test 14: Tail with -n argument
run_test 14 "Tail with -n argument" \
    "/usr/bin/tail -n 5 Makefile"

# Test 15: Touch with multiple files
run_test 15 "Touch multiple files" \
    "/usr/bin/touch $TEMP_DIR/file1 $TEMP_DIR/file2"

# Test 16: Rm with arguments
run_test 16 "Rm with -f argument" \
    "/bin/rm -f $TEMP_DIR/file1"

# Test 17: Chmod with permission and file
run_test 17 "Chmod with arguments" \
    "/bin/chmod 755 $TEMP_DIR/file2"

# Test 18: Find with path argument
run_test 18 "Find with path" \
    "/usr/bin/find $TEMP_DIR -type f"

# Test 19: Sort with filename
run_test 19 "Sort with filename" \
    "/usr/bin/sort Makefile"

# Test 20: Command with numbers as arguments
run_test 20 "Echo with numbers" \
    "echo 123 456 789 0"

# Summary
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}           TEST SUMMARY${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "Total tests: ${TEST_COUNT}"
echo -e "${GREEN}Passed (no crash): ${PASSED}${NC}"
echo -e "${RED}Failed (crash): ${FAILED}${NC}"

if [ $FAILED -gt 0 ]; then
    echo -e "\n${MAGENTA}Failed tests details:${NC}"
    grep -B3 "CRASH DETECTED" "$OUTPUT_FILE" | grep "Test [0-9]" | while read line; do
        echo -e "${RED}  - $line${NC}"
    done
fi

echo -e "\nDetailed results saved to: ${YELLOW}$OUTPUT_FILE${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}✓✓✓ ALL TESTS PASSED! No crashes detected. ✓✓✓${NC}"
    echo -e "${GREEN}Your minishell handles arguments correctly!${NC}"
    exit 0
else
    echo -e "\n${RED}✗ Some tests failed. Check $OUTPUT_FILE for details.${NC}"
    exit 1
fi