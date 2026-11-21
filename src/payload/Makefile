# Entry4 payload (1402) — visual rebuild
# Usage:
#   python build.py            # rebuild out/entry4.bin (core-exact if visuals unchanged)
#   nmake /f Makefile          # same via Makefile (Windows)
#   make                       # same (Unix)

!IFNDEF PYTHON
PYTHON = python
!ENDIF

all:
	$(PYTHON) build.py

check:
	$(PYTHON) build.py --check-only

clean:
	-@rmdir /s /q out 2>nul || rm -rf out
