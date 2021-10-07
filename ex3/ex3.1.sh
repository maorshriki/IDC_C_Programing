cp /share/ex_data/ex3/address_book.txt /share/ex_data/ex3/story.txt .
grep -E "^[[:alpha:]]{5,}\- " address_book.txt | sort -k1,1 > long_names.txt
grep "[^N].$" address_book.txt | tr "-" ":" | cut -d" " -f1,5 > non-N-states.txt
grep " Street ..$" address_book.txt | sed -r 's/^([[:alpha:]]+)\- ([0-9]+) ([[:alpha:]]+) Street (..)$/\1 lives in the state of \4, at this address: \2 \3 Street/' > live_in_street.txt
cat story.txt | tr [:punct:][:space:] "\n" | tr -s "\n" | grep -E "^[[:alpha:]]{4,}$" | grep "[Uu]" -c 
cat story.txt | tr [:punct:][:space:] "\n" | tr -s "\n" | tr "A-Z" "a-z" | grep -E "^([[:alpha:]]*[aeiou]){4}[[:alpha:]]*$" | sort | uniq | wc -l | sed -r 's/(.*)/The number of distinct proper words in story.txt that contain at least 4 vowels is \1/'
