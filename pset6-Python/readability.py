
text = input('Please input your text: ')
word_count = 0
letter_count = 0
sentence_count = 0

for sentence in text.split(['?','.','!']):
    sentence_count += 1

    for word in sentence.split(' '):
        # Count number of words
        word_count += 1

        for letter in word:
            letter_count += 1

L = letter_count * 100 / word_count
S = sentence_count * 100 / word_count
CL_index = 0.0588 * L - 0.296 * S - 15.8
print(f"Grade level is {CL_index}")