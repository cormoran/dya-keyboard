QMK = qmk
KB = dya
KM = default

init:
	git submodule update --remote
	git submodule update --init --recursive

compile:
	mkdir -p ./firmware/qmk_firmware/keyboards/tmp
	ln -sn $(shell pwd)/firmware/qmk/keyboards/${KB} firmware/qmk_firmware/keyboards/tmp/${KB} || true
	cd firmware/qmk_firmware; ${QMK} compile -kb tmp/${KB} -km ${KM}

flash:
	cd firmware/qmk_firmware; ${QMK} flash -kb tmp/${KB} -km ${KM}

clean:
	rm -rf firmware/qmk_firmware/keyboards/tmp
	cd firmware/qmk_firmware; ${QMK} clean
