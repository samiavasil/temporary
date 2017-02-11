#Configure Openssl path
OPEN_SSL_INCLUDE_PATH = C:\Projects\Fiat\workspace\openssl-1.0.0e-mingw64\mingw64\include
OPEN_SSL_LIB_PATH = C:\Projects\Fiat\workspace\openssl-1.0.0e-mingw64\mingw64\lib

TEMPLATE = subdirs
SUBDIRS +=    serial_plugin \
              hexedit_plugin \
              portio_simulator_plugin \
              data_plot_plugin \
              tcpip_plugin \
              diagram_plugin \
              template_plugin \
              template_designer_plugin \
              fra_plugin \
              qt_designer_plugin \


exists( $$OPEN_SSL_INCLUDE_PATH/openssl/rsa.h ) {
exists( $$OPEN_SSL_LIB_PATH/libcrypto.a ) {
      message( "Openssl Founded: Configure crypto plugin for build" )
SUBDIRS += crypto_plugin
}
}

#
#

