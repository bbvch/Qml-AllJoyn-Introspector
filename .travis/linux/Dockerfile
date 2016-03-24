FROM rabits/qt:5.4-desktop

USER root

RUN apt-get -qq update && apt-get -qq install -f unzip scons libcap-dev libssl-dev libxml2-dev xsltproc

RUN cd /opt && \
	curl https://mirrors.kernel.org/allseenalliance/alljoyn/15.09/alljoyn-15.09.00a-src.tar.gz -o alljoyn-15.09.00a-src.tar.gz && \
	tar xf alljoyn-15.09.00a-src.tar.gz && \
	rm -f alljoyn-15.09.00a-src.tar.gz && \
	cd alljoyn-15.09.00a-src && \
	scons BINDINGS=cpp && \
	mv build/linux/x86_64/debug/dist /opt/alljoyn-linux && \
	cd /opt && \
	rm -fr alljoyn-15.09.00a-src

ENV AJ_DIST=/opt/alljoyn-linux

RUN apt-get -qq install -f software-properties-common && add-apt-repository ppa:ubuntu-toolchain-r/test && apt-get -qq update

RUN apt-get -qq install -f gcc-4.9 g++-4.9 && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.9

RUN apt-get -qq install -f cmake wget unzip

RUN cd /usr/src && \
wget https://github.com/google/googletest/archive/master.zip && \
unzip master.zip && \
mv googletest-master/googlemock googlemock && \
ln -s googlemock gmock && \
mv googletest-master/googletest googletest && \
ln -s googletest gtest && \
rm -fr master.zip googletest-master && \
cd /usr/include && \
ln -s /usr/src/googlemock/include/gmock && \
ln -s /usr/src/googletest/include/gtest

RUN apt-get -qq clean

ADD build.sh /

