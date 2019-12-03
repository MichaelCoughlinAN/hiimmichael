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


def main():
    english_words = load_words()

    # Define a word limit used to define the amount of words discovered on a website
    word_limit = 85

    list1 = ['https://www.bbc.co.uk/', 'https://news.google.com/?hl=en-US&gl=US&ceid=US:en', 'https://www.npr.org/']
    web_site_address = random.choice(list1)

    print('Scanning ' + web_site_address + ' for a list of valid words ...')
    page = requests.get(web_site_address)

    if not page:
        print('An error has occurred parsing website ...')
        return

    # Remove non-alphabet chars from string
    content = re.sub(r'[^a-zA-Z ]+', ' ', strip_tags(page.content.decode('utf-8')))
    # Create lists that will be used to contain the found words
    words_list = list()

    text = nltk.word_tokenize(content)
    result = nltk.pos_tag(text)

    # Split the website content string at every whitespace creating an array of potentially usable words
    for entry in result:
        word = entry[0].strip()
        word = word.lower()

        # Get syllable count of word and verify word is not a single article or exceeds syllable count
        syllable_count = textstat.syllable_count(word)

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