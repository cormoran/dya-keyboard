QMK = qmk
KB = dya
KM = default

init:
	git submodule update --remote
	git submodule update --init --recursive

compile:
	mkdir -p ./farms/qmk_firmware/keyboards/tmp
	ln -sn $(shell pwd)/farms/qmk/keyboards/${KB} farms/qmk_firmware/keyboards/tmp/${KB} || true
	cd farms/qmk_firmware; ${QMK} compile -kb tmp/${KB} -km ${KM}

clean:
	rm -rf farms/qmk_firmware/keyboards/tmp
	cd farms/qmk_firmware; ${QMK} clean
