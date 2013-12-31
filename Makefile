.PHONY: linux-alsa linux-jack

linux-alsa:
	$(MAKE) -C chuck linux-alsa

linux-jack:
	$(MAKE) -C chuck linux-jack

clean:
	$(MAKE) -C chuck clean
