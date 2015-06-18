#!/bin/bash
./arrowkey | while read -r -n 1 c; do
d=$(LC_TYPE=C printf '%d\n' "'$c")
if [ "$d" == "8" ]; then
    c="BackSpace"
elif [ "$d" == "0" ]; then
    c="space"
elif [ "$c" == "\\" ]; then
    c="backslash"
elif [ "$c" == "!" ]; then
    c="exclam"
elif [ "$c" == "~" ]; then
    c="asciitilde"
elif [ "$c" == "\`" ]; then
    c="quoteleft"
elif [ "$c" == "@" ]; then
    c="ampersand"
elif [ "$c" == "#" ]; then
    c="numbersign"
elif [ "$c" == "$" ]; then
    c="dollar"
elif [ "$c" == "%" ]; then
    c="percent"
elif [ "$c" == "^" ]; then
    c="asciicircum"
elif [ "$c" == "&" ]; then
    c="ampersand"
elif [ "$c" == "*" ]; then
    c="asterisk"
elif [ "$c" == "(" ]; then
    c="parenleft"
elif [ "$c" == ")" ]; then
    c="parenright"
elif [ "$c" == "-" ]; then
    c="minus"
elif [ "$c" == "=" ]; then
    c="equal"
elif [ "$c" == "_" ]; then
    c="underscore"
elif [ "$c" == "+" ]; then
    c="plus"
elif [ "$c" == "[" ]; then
    c="bracketleft"
elif [ "$c" == "]" ]; then
    c="bracketright"
elif [ "$c" == "{" ]; then
    c="braceleft"
elif [ "$c" == "}" ]; then
    c="braceright"
elif [ "$c" == "|" ]; then
    c="bar"
elif [ "$c" == ";" ]; then
    c="semicolon"
elif [ "$c" == "'" ]; then
    c="quoteright"
elif [ "$c" == ":" ]; then
    c="colon"
elif [ "$c" == "\"" ]; then
    c="quotedbl"
elif [ "$c" == "," ]; then
    c="comma"
elif [ "$c" == "." ]; then
    c="period"
elif [ "$c" == "/" ]; then
    c="slash"
elif [ "$c" == "<" ]; then
    c="less"
elif [ "$c" == ">" ]; then
    c="greater"
elif [ "$c" == "?" ]; then
    c="question"
fi
    xdotool search Firefox keydown "$c" keyup "$c"
done
