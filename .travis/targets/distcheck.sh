build() {
    default_configure \
        --enable-examples
    make distcheck
}

deploy() {
    FILES=( *.{*.tar.{gz,bz2,xz},zip} )
    [[ ${RV} -eq 0 ]] && [[ "x${CC}" = "xgcc" ]]
}
