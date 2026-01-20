#!/usr/bin/env bash
#!/usr/bin/env bash
set -e
ROOT_DIR=$(pwd)
LOG=tests/test_output.log
rm -f "$LOG"
print() { echo -e "$1" | tee -a "$LOG"; }

run_here() {
  label="$1"
  print "--- TEST: $label ---"
  tmpf=$(mktemp)
  cat > "$tmpf"
  ./minishell < "$tmpf" 2>&1 | tee -a "$LOG"
  print "EXIT:$?\n"
  rm -f "$tmpf"
}

print "Building project (make)"
make -s | tee -a "$LOG" || { print "make failed"; exit 1; }

# Simple builtins
run_here "echo hello" <<'INPUT'
echo hello
exit
INPUT
run_here "pwd after cd" <<'INPUT'
cd ..
pwd
exit
INPUT
run_here "export and echo" <<'INPUT'
export X_TEST=ok
echo "$X_TEST"
exit
INPUT
run_here "unset and echo" <<'INPUT'
unset X_TEST
echo "${X_TEST-}"
exit
INPUT

# External exec and PATH resolution
run_here "absolute ls" <<'INPUT'
/bin/ls -1
exit
INPUT
run_here "relative ls" <<'INPUT'
ls -1
exit
INPUT
run_here "nonexistent path" <<'INPUT'
./nonexistent && echo should_not_run
exit
INPUT

# Permissions vs not-found
print "--- TEST: permission vs not-found ---"
rm -f tmp_exec || true
touch tmp_exec
chmod 644 tmp_exec
tmpf=$(mktemp)
cat > "$tmpf" <<'INPUT'
./tmp_exec
exit
INPUT
./minishell < "$tmpf" 2>&1 | tee -a "$LOG"
print "EXIT:$?"
rm -f tmp_exec "$tmpf"

run_here "no such cmd" <<'INPUT'
./no_such_cmd
exit
INPUT

# Single pipe
run_here "echo hi | wc -c" <<'INPUT'
echo hi | wc -c
exit
INPUT

# Multiple pipes
run_here "seq|awk sum" <<'INPUT'
seq 1 5 | awk '{sum+=$1} END {print sum}'
exit
INPUT

# Pipeline with builtin in middle
run_here "builtin in middle" <<'INPUT'
echo foo | sed 's/foo/bar/' | cat
exit
INPUT

# Redirections
run_here "redir overwrite" <<'INPUT'
echo abc > /tmp/minitest
cat < /tmp/minitest
rm /tmp/minitest
exit
INPUT
run_here "redir append" <<'INPUT'
echo end >> /tmp/minitest
cat /tmp/minitest
rm /tmp/minitest
exit
INPUT

# Heredoc
run_here "heredoc cat" <<'INPUT'
cat <<EOF
line1
line2
EOF
exit
INPUT

# Mixed redir + pipes
run_here "mixed redir+pipe" <<'INPUT'
echo hello > /tmp/hi
cat /tmp/hi | wc -c
rm /tmp/hi
exit
INPUT

print "Tests complete. See $LOG for full output."

exit 0
