FROM rabits/qt:5.4-android

USER root

RUN apt-get -qq update && apt-get -qq install -f unzip

RUN cd /opt && \
	curl https://mirrors.kernel.org/allseenalliance/alljoyn/15.09/alljoyn-15.09.00a-android-sdk-rel.zip -o alljoyn-15.09.00a-android-sdk-rel.zip && \
	unzip alljoyn-15.09.00a-android-sdk-rel.zip && \
	mv alljoyn-android/core/alljoyn-15.09.00a-rel/ /opt/alljoyn-android-new && \
	rm -rf alljoyn-15.09.00a-android-sdk-rel.zip alljoyn-android && \
	mv alljoyn-android-new alljoyn-android

ENV AJ_DIST=/opt/alljoyn-android
ENV ANDROID_NDK_PLATFORM=android-19

ADD build.sh /
