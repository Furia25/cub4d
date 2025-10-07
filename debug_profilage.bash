#!/bin/bash

# === CONFIGURATION ===
EXEC_NAME="cub3d maps/test.cub"
OUT_FILE="callgrind.out"
PROFILING_OUTPUT="debug_profilage.txt"

# === PROFILAGE ===
echo "[+] Profiling with Valgrind..."
valgrind --tool=callgrind --callgrind-out-file=$OUT_FILE ./$EXEC_NAME

# === ANALYSE TEXTUELLE ===
echo "[+] Annotating Callgrind output..."
callgrind_annotate $OUT_FILE > $PROFILING_OUTPUT

echo "[+] Profiling summary written to $PROFILING_OUTPUT"

# === LANCER KCACHEGRIND (si dispo) ===
if command -v kcachegrind >/dev/null 2>&1; then
	echo "[+] Opening in KCachegrind..."
	kcachegrind $OUT_FILE &
else
	echo "[!] KCachegrind not found. Skipping GUI analysis."
fi

