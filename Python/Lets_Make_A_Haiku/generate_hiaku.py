#!/usr/bin/env python

# Michael Coughlin
# hiimmichael.com
# 2019

import json
import os
import random
import re
import nltk
import requests
from textstat.textstat import textstat
import string
from nltk.corpus import cmudict
cmu = cmudict.dict()

CONTRACTION_MAP = {
"ain't": "is not",
"aren't": "are not",
"can't": "cannot",
"can't've": "cannot have",
"'cause": "because",
"could've": "could have",
"couldn't": "could not",
"couldn't've": "could not have",
"didn't": "did not",
"doesn't": "does not",
"don't": "do not",
"hadn't": "had not",
"hadn't've": "had not have",
"hasn't": "has not",
"haven't": "have not",
"he'd": "he would",
"he'd've": "he would have",
"he'll": "he will",
"he'll've": "he he will have",
"he's": "he is",
"how'd": "how did",
"how'd'y": "how do you",
"how'll": "how will",
"how's": "how is",
"I'd": "I would",
"I'd've": "I would have",
"I'll": "I will",
"I'll've": "I will have",
"I'm": "I am",
"I've": "I have",
"i'd": "i would",
"i'd've": "i would have",
"i'll": "i will",
"i'll've": "i will have",
"i'm": "i am",
"i've": "i have",
"isn't": "is not",
"it'd": "it would",
"it'd've": "it would have",
"it'll": "it will",
"it'll've": "it will have",
"it's": "it is",
"let's": "let us",
"ma'am": "madam",
"mayn't": "may not",
"might've": "might have",
"mightn't": "might not",
"mightn't've": "might not have",
"must've": "must have",
"mustn't": "must not",
"mustn't've": "must not have",
"needn't": "need not",
"needn't've": "need not have",
"o'clock": "of the clock",
"oughtn't": "ought not",
"oughtn't've": "ought not have",
"shan't": "shall not",
"sha'n't": "shall not",
"shan't've": "shall not have",
"she'd": "she would",
"she'd've": "she would have",
"she'll": "she will",
"she'll've": "she will have",
"she's": "she is",
"should've": "should have",
"shouldn't": "should not",
"shouldn't've": "should not have",
"so've": "so have",
"so's": "so as",
"that'd": "that would",
"that'd've": "that would have",
"that's": "that is",
"there'd": "there would",
"there'd've": "there would have",
"there's": "there is",
"they'd": "they would",
"they'd've": "they would have",
"they'll": "they will",
"they'll've": "they will have",
"they're": "they are",
"they've": "they have",
"to've": "to have",
"wasn't": "was not",
"we'd": "we would",
"we'd've": "we would have",
"we'll": "we will",
"we'll've": "we will have",
"we're": "we are",
"we've": "we have",
"weren't": "were not",
"what'll": "what will",
"what'll've": "what will have",
"what're": "what are",
"what's": "what is",
"what've": "what have",
"when's": "when is",
"when've": "when have",
"where'd": "where did",
"where's": "where is",
"where've": "where have",
"who'll": "who will",
"who'll've": "who will have",
"who's": "who is",
"who've": "who have",
"why's": "why is",
"why've": "why have",
"will've": "will have",
"won't": "will not",
"won't've": "will not have",
"would've": "would have",
"wouldn't": "would not",
"wouldn't've": "would not have",
"y'all": "you all",
"y'all'd": "you all would",
"y'all'd've": "you all would have",
"y'all're": "you all are",
"y'all've": "you all have",
"you'd": "you would",
"you'd've": "you would have",
"you'll": "you will",
"you'll've": "you will have",
"you're": "you are",
"you've": "you have"
}

class Word:
    def __init__(self, word, syllables, pos_tag):
        self.word = word
        self.syllables = syllables
        self.pos_tag = pos_tag

    def get_word(self):
        return self.word

    def get_syllables(self):
        return self.syllables

    def get_pos_tag(self):
        return self.pos_tag


# Remote HTML tags from a String
# html: String
def strip_tags(html):
    print('Stripping HTML tag elements from fetched web data ...\n')
    clean_re = re.compile('<.*?>')
    return re.sub(clean_re, '', html)


def assemble_haiku_author():
    return 'By: ' + os.environ['COMPUTERNAME']


def assemble_haiku_title(word_bank):
    # Pick a random number between 1 and 10
    syllable_line_count = random.randint(1, 10)

    haiku = ''
    # A list used to prevent duplicate words in the same line
    used_words = list()

    while syllable_line_count != 0:
        # Randomly select a word from the array of valid words found while parsing website
        word_object = random.choice(word_bank)
        # Get syllable count of word
        word = word_object.get_word()
        syllable_count = word_object.get_syllables()

        # Continue if the syllable count of the randomly selected word does not exceed the remaining syllable count
        if not syllable_count > syllable_line_count and word not in used_words:
            # Remove word from valid words array to avoid duplicate usage of word
            used_words.append(word)
            # Adjust the syllable count accordingly
            syllable_line_count = syllable_line_count - syllable_count
            haiku = haiku + word + ' '

    return haiku


def assemble_haiku_line(word_bank, syllable_line_count):
    haiku = ''
    # A list used to prevent duplicate words in the same line
    used_words = list()

    while syllable_line_count != 0:
        # Randomly select a word from the array of valid words found while parsing website
        word_object = random.choice(word_bank)
        # Get syllable count of word
        word = word_object.get_word()
        syllable_count = word_object.get_syllables()

        # Continue if the syllable count of the randomly selected word does not exceed the remaining syllable count
        if not syllable_count > syllable_line_count and word not in used_words:
            # Remove word from valid words array to avoid duplicate usage of word
            used_words.append(word)
            # Adjust the syllable count accordingly
            syllable_line_count = syllable_line_count - syllable_count
            haiku = haiku + word + ' '

    return haiku


def load_words():
    try:
        filename = os.path.join(os.getcwd(), "words_dictionary.json")
        with open(filename, "r") as english_dictionary:
            valid_words = json.load(english_dictionary)
            return valid_words
    except Exception as e:
        return str(e)


def count_syllables(word):
    if word in cmu:
        return max([len([y for y in x if y[-1] in string.digits])
                    for x in cmu[word]])


def expand_contractions(text, contraction_mapping=CONTRACTION_MAP):
    contractions_pattern = re.compile('({})'.format('|'.join(contraction_mapping.keys())),
                                      flags=re.IGNORECASE | re.DOTALL)

    def expand_match(contraction):
        match = contraction.group(0)
        first_char = match[0]
        expanded_contraction = contraction_mapping.get(match) \
            if contraction_mapping.get(match) \
            else contraction_mapping.get(match.lower())
        expanded_contraction = first_char + expanded_contraction[1:]
        print('Expanded: ' + expanded_contraction)
        return expanded_contraction

    expanded_text = contractions_pattern.sub(expand_match, text)
    expanded_text = re.sub("'", "", expanded_text)
    return expanded_text


def main():
    english_words = load_words()

    # Define a word limit used to define the amount of words discovered on a website
    word_limit = 1024

    list1 = ['https://www.bbc.co.uk/', 'https://news.google.com/?hl=en-US&gl=US&ceid=US:en', 'https://www.npr.org/']
    web_site_address = random.choice(list1)

    print('Scanning ' + web_site_address + ' for a list of valid words ...')
    page = requests.get(web_site_address)

    if not page:
        print('An error has occurred parsing website ...')
        return

    content = strip_tags(page.content.decode('utf-8'))
    # content = expand_contractions(content)

    # Remove non-alphabet chars from string
    content = re.sub(r'[^a-zA-Z ]+', ' ', content)

    # Create lists that will be used to contain the found words
    words_list = list()

    text = nltk.word_tokenize(content)
    result = nltk.pos_tag(text)

    print(result)

    # Split the website content string at every whitespace creating an array of potentially usable words
    for entry in result:
        word = entry[0].strip()
        word = word.lower()

        # Get syllable count of word and verify word is not a single article or exceeds syllable count
        syllable_count = count_syllables(word)
        try:
            # Check if syllable count of word exceeds max haiku syllable line count
            if syllable_count <= 7:
                dupe = False

                try:
                    if english_words[word] == 1:
                        for word1 in words_list:
                            if word == word1.get_word():
                                dupe = True
                                break;

                        if not dupe:
                            words_list.append(Word(word, syllable_count, entry[1]))
                            print('Added "' + word + '" to haiku word bank ... word count is now [' + str(len(words_list)) + ']')

                            # Place a hard limit on the amount of words in the valid_english_words array
                            # This is mainly used to reduce amount of time spent scanning and parsing website page content
                            # when more than enough words have been found
                            if (len(words_list) + 1) > word_limit:
                                print('\nMore than enough words found, exiting word discovery loop ...')
                                break
                except KeyError:
                    pass
        except TypeError:
            pass

    print('----------------------------------')
    print('\nA Haiku')
    print(assemble_haiku_author() + '\n')
    print(assemble_haiku_line(words_list, 5))
    print(assemble_haiku_line(words_list, 7))
    print(assemble_haiku_line(words_list, 5))
    print('\n----------------------------------')
    print('This poem was randomly generated')
    print('Word source: ' + web_site_address)
    print('Copywrite @ 2019 https://hiimmichael.com/')


if __name__ == "__main__":
    main()