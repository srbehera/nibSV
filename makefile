NIMBLE_DIR?=${CURDIR}/nimbleDir
export NIMBLE_DIR
# Alternatively, use --nimbleDir:${NIMBLE_DIR} everywhere

build:
	nim c src/nib.nim
all:
	${MAKE} install
quick:
	nim c -r tests/t_kmers.nim
	nim c -r tests/t_util.nim
help:
	nimble -h
	nimble tasks
tests:
	@# much faster than nimble
	${MAKE} -C tests
test:
	nimble test  # uses "tests/" directory by default
integ-test:
	@echo 'integ-test TBD'
install:
	nimble install -y
pretty:
	find src -name '*.nim' | xargs -L1 nimpretty --indent=4 --maxLineLen=1024
	find tests -name '*.nim' | xargs -L1 nimpretty --indent=4 --maxLineLen=1024
setup: rsync
	nimble install --verbose -y hts kmer bitvector cligen
rsync:
	mkdir -p ${NIMBLE_DIR}/pkgs/
	rsync -av vendor/STRling/ ${NIMBLE_DIR}/pkgs/strling-0.3.0/
	rsync -av vendor/threadpools/ ${NIMBLE_DIR}/pkgs/threadpools-0.1.0/

.PHONY: test tests
