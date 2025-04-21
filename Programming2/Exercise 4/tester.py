#!/usr/bin/env python3
"""
Improved test harness for C project with newline and whitespace normalization.

This script runs all test cases found in the `stdin` and `stdout` folders,
normalizes line endings and whitespace, and compares the program's output
to the expected results.

Usage:
    python tester.py [--exe EXECUTABLE] [--in-dir STDIN_DIR] [--out-dir STDOUT_DIR]

Defaults:
    EXECUTABLE: ./cmake-build-debug/z4
    STDIN_DIR:   ./stdin
    STDOUT_DIR:  ./stdout
"""
import os
import sys
import argparse
import subprocess
import difflib

def normalize(text_bytes):
    """Decode bytes, normalize line endings and reduce whitespace."""
    text = text_bytes.decode(errors='replace')
    text = text.replace('\r\n', '\n')
    lines = text.strip().split('\n')
    # Normalize each line: strip and reduce multiple spaces/tabs to one space
    norm_lines = [' '.join(line.strip().split()) for line in lines if line.strip() != '']
    return '\n'.join(norm_lines)


def run_tests(exe_path, stdin_dir, stdout_dir):
    if not os.path.isfile(exe_path):
        print(f"Error: Executable not found at '{exe_path}'", file=sys.stderr)
        sys.exit(1)

    scenarios = sorted(
        entry for entry in os.listdir(stdin_dir)
        if os.path.isdir(os.path.join(stdin_dir, entry))
    )
    total = passed = 0

    for scen in scenarios:
        in_folder = os.path.join(stdin_dir, scen)
        out_folder = os.path.join(stdout_dir, scen)
        if not os.path.isdir(out_folder):
            print(f"Warning: No expected-output folder for scenario '{scen}'")
            continue

        for fname in sorted(os.listdir(in_folder)):
            in_file = os.path.join(in_folder, fname)
            expected_file = os.path.join(out_folder, fname)

            with open(in_file, 'rb') as f:
                input_data = f.read()

            proc = subprocess.run([exe_path], input=input_data,
                                  stdout=subprocess.PIPE,
                                  stderr=subprocess.PIPE)
            actual_norm = normalize(proc.stdout)

            if not os.path.isfile(expected_file):
                print(f"{scen}/{fname}: Missing expected file '{expected_file}'")
                continue

            with open(expected_file, 'rb') as f:
                expected_norm = normalize(f.read())

            total += 1
            if actual_norm == expected_norm:
                print(f"{scen}/{fname}: PASS")
                passed += 1
            else:
                print(f"{scen}/{fname}: FAIL")
                print("--- Input ---")
                print(normalize(input_data))
                print("--- Expected ---")
                print(expected_norm)
                print("--- Actual ---")
                print(actual_norm)
                print("--- Diff ---")
                diff = difflib.unified_diff(
                    expected_norm.splitlines(),
                    actual_norm.splitlines(),
                    fromfile='expected',
                    tofile='actual',
                    lineterm=''
                )
                for line in diff:
                    print(line)
                print("=" * 60)

    print(f"\nSummary: {passed}/{total} tests passed.")
    return passed, total

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Run test cases for the C project.")
    parser.add_argument('--exe', '-e', default='./cmake-build-debug/z4.exe',
                        help='Path to the compiled executable')
    parser.add_argument('--in-dir', '-i', default='./stdin',
                        help='Directory containing input scenarios')
    parser.add_argument('--out-dir', '-o', default='./stdout',
                        help='Directory containing expected outputs')
    args = parser.parse_args()

    run_tests(args.exe, args.in_dir, args.out_dir)