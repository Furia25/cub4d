#!/bin/bash
source ~/env/bin/activate
ressources/create_random $1 $2 > output && python3 ressources/test_rng.py
rm output