#!/bin/bash
arrowkey | while read -r -n 1 c; do
    d=$(LC_TYPE=C printf '%d\n' "'$c")
    # this lookup array indexes special keys for X
    declare -A keys=( ["\\"]="backslash" ["!"]="exclam" ["~"]="asciitilde"
        ["\`"]="quoteleft" ["@"]="ampersand" ["#"]="numbersign" ["$"]="dollar"
        ["%"]="percent" ["^"]="asciicircum" ["&"]="ampersand" ["*"]="asterisk"
        ["("]="parenleft" [")"]="parenright" ["-"]="minus" ["="]="equal"
        ["_"]="underscore" ["+"]="plus" ["["]="bracketleft"
        ["]"]="bracketright" ["{"]="braceleft" ["}"]="braceright" ["|"]="bar"
        [";"]="semicolon" ["'"]="quoteright" [":"]="colon" ["\""]="quotedbl"
        [","]="comma" ["."]="period" ["/"]="slash" ["<"]="less" [">"]="greater"
        ["?"]="question" )
    if [ "$d" == "8" ]; then
        c="BackSpace"
    elif [ "$d" == "0" ]; then
        c="space"
    elif [ "${keys[$c]}" != "" ]; then
        c="${keys[$c]}"
    fi
    xdotool search Firefox keydown "$c" keyup "$c"
done
