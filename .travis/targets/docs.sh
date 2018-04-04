build() {
    default_configure \
        --enable-doc
    make docs

    local pn="$(grep PACKAGE_TARNAME config.h | cut -d\" -f2)"
    local pv="$(grep PACKAGE_VERSION config.h | cut -d\" -f2)"
    local p="${pn}-docs-${pv}"
    local docs="doc/build/html"

    [[ -d "${docs}" ]]

    mv "${docs}" docs
    tar \
        -cvJf "${p}.tar.xz" \
        docs
}

deploy() {
    FILES=( *.tar.xz )
    [[ ${RV} -eq 0 ]]
}

extract() {
    grep .
}
