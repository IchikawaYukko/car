# RPM package build environment
FROM	fedora:42

RUN	dnf install -y git make gcc ncurses-devel rpm-build rpm-sign && \
	git clone https://github.com/IchikawaYukko/car.git && \
	cd car && \
	git checkout buildrpm && \
	make rpm
