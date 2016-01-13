(quote {
    :name "package-name"

    :version "1.0.0"

    :description "a package.lisp example"

    :main "./path/to/index.lisp"

    :license "./path/to/license" ; or { :name "Name" :url "http://url.com" }

    :dependencies {
        "dependency-one" "git://github.com/nathanfaucett/dependency-one.git"
        "dependency-two" "git://github.com/nathanfaucett/dependency-two#commit.git"
    }

    :dev-dependencies {
        "dependency-one" "git://github.com/nathanfaucett/dependency-one.git"
        "dependency-two" "git://github.com/nathanfaucett/dependency-two.git#commit-ish"
    }
})
