cp /share/ex_data/ex2/story.txt .
cat story.txt | tr [:punct:][:space:] "\n" | tr -s "\n" | tr "A-Z" "a-z" | sort | uniq -c > story-words.txt
cat story.txt | tr [:punct:][:space:] "\n" | tr -s "\n" | tr "a-z" "A-Z" | sort | uniq | cut -c1 | uniq -c | tail -n+11 > story-stats.txt 
cat story.txt | tr "Oo\n" "\n\n " | wc -l > story-num-os.txt
