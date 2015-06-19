#!/bin/bash
arrowkey | while read -r -n 1 c; do
    d=$(LC_TYPE=C printf '%d\n' "'$c")
    # this lookup array indexes special keys for X
    declare -A keys=( ["a\\"]="backslash" ["a!"]="exclam" ["a~"]="asciitilde"
        ["a\`"]="quoteleft" ["a@"]="at" ["a#"]="numbersign" ["a$"]="dollar"
        ["a%"]="percent" ["a^"]="asciicircum" ["a&"]="ampersand" ["a*"]="asterisk"
        ["a("]="parenleft" ["a)"]="parenright" ["a-"]="minus" ["a="]="equal"
        ["a_"]="underscore" ["a+"]="plus" ["a["]="bracketleft"
        ["a]"]="bracketright" ["a{"]="braceleft" ["a}"]="braceright" ["a|"]="bar"
        ["a;"]="semicolon" ["a'"]="quoteright" ["a:"]="colon" ["a\""]="quotedbl"
        ["a,"]="comma" ["a."]="period" ["a/"]="slash" ["a<"]="less" ["a>"]="greater"
        ["a?"]="question" )
    if [ "$d" == "8" ]; then
        c="BackSpace"
    elif [ "$d" == "0" ]; then
        c="space"
    elif [ "${keys[a$c]}" != "" ]; then
        c="${keys[a$c]}"
    fi
    xdotool search Firefox keydown "$c" keyup "$c"
done
