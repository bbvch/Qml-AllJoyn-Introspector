FROM rabits/qt:5.4-android

USER root

RUN apt-get -qq update && apt-get -qq install -f unzip

RUN cd /opt && curl https://mirrors.kernel.org/allseenalliance/alljoyn/15.09/alljoyn-15.09.00a-android-sdk-rel.zip -o alljoyn-15.09.00a-android-sdk-rel.zip && unzip alljoyn-15.09.00a-android-sdk-rel.zip && rm -f alljoyn-15.09.00a-android-sdk-rel.zip

ENV AJ_DIST=/opt/alljoyn-android/core/alljoyn-15.09.00a-rel/

