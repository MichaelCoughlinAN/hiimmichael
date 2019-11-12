#!/usr/bin/env python
import requests
import re
from HTMLParser import HTMLParser
from lxml import html
from textstat.textstat import textstat
from nltk.corpus import words
from nltk.corpus import wordnet as wn
import nltk
import random
import json
import os
import sys
import time


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


# Class used to strip HTML tags from page.content
class MLStripper(HTMLParser):
    def __init__(self):
        self.reset()
        self.fed = []

    def handle_data(self, d):
        d = d + ' '
        self.fed.append(d)

    def get_data(self):
        return ''.join(self.fed)


# Remote HTML tags from a String
# html: String
def strip_tags(html):
    s = MLStripper()
    s.feed(html)
    return s.get_data()


def assemble_haiku_author():
    return 'By: ' +  os.environ['COMPUTERNAME']


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
            # print 'Syllables remaining: ' + str(syllable_line_count)
            # print haiku

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
            #print 'Syllables remaining: ' + str(syllable_line_count)
            #print haiku

    return haiku


def load_words():
    try:
        filename = os.path.join(os.getcwd(), "words_dictionary.json")
        with open(filename,"r") as english_dictionary:
            valid_words = json.load(english_dictionary)
            return valid_words
    except Exception as e:
        return str(e)


def main():
    english_words = load_words()
    # Define a word limit used to define the amount of words discovered on a website
    # Uncomment to download nltk if not already downloaded
    # nltk.download('all')

    while True:
        try:
            web_site_address = raw_input("Please enter the URL of a website: ")
            #web_site_address = 'http://www.google.com'
            page = requests.get(web_site_address)
            print 'Scanning ' + web_site_address + ' for a list of valid English words!'
            break
        except Exception, e:
            print 'Incorrect website, please try again (e.g. http://www.google.com)'

    while True: # This is a development loop to weed out unwanted programmer jargon words

        # Remove non-alphabet chars from string
        content = re.sub(r'[^a-zA-Z ]+', ' ', strip_tags(page.content))
        # Create lists that will be used to contain the found words
        words_list = list()

        text = nltk.word_tokenize(content)
        result = nltk.pos_tag(text)

        # Split the website content string at every whitespace creating an array of potentially usable words
        for entry in result:
            word = entry[0].strip()
            # Check if word is a valid English word and not a word associated with a programming language
            #if word not in programmer_jargon:
                # Lowercase the word
            word = word.lower()
                # Get syllable count of word and verify word is not a single article or exceeds syllable count
            syllable_count = textstat.syllable_count(word)
                # Check if syllable count of word exceeds max haiku syllable line count
            if syllable_count <= 7:
                try:
                    if english_words[word] == 1:
                         #print 'Adding "' + word + '" to Haiku word bank'
                        words_list.append(Word(word, syllable_count, entry[1]))
                except Exception, e:
                    pass

            # Place a hard limit on the amount of words in the valid_english_words array
            # This is mainly used to reduce amount of time spent scanning and parsing website page content
            # when more than enough words have been found
            #if len(words_list) > word_limit:
             #   print 'More than enough words found, exiting word discovery loop...'
                #break
        print assemble_haiku_title(words_list)
        print assemble_haiku_author()
        print
        print assemble_haiku_line(words_list, 5)
        print assemble_haiku_line(words_list, 7)
        print assemble_haiku_line(words_list, 5)

        print '----------------------------------'
        time.sleep(20)

if __name__ == "__main__":
    main()







