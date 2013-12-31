.PHONY: linux-alsa linux-jack clean

CHUCK_SRC=chuck/src

linux-alsa:
	$(MAKE) -C chuck linux-alsa

linux-jack:
	$(MAKE) -C chuck linux-jack

clean:
	$(MAKE) -C $(CHUCK_SRC) clean
