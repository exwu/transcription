# transcription

A GUI to help me transcribe my handwritten novel. With some aspirations of machine learning my handwriting so one day I won't have to. 

Some transcribing standards to follow:

- Scene breaks (handwritten as a long line) should be transcribed as ```---```
- Paragraphs are delineated by double new lines
- Try and put the new lines in when paragraph breaks correspond with new pages
- In text comments are transcribed in ``` (( double parentheses )) ```
- Moving blocks of text should be done using asterisks and commented text blocks, e.g. ```*(( move this )) here *```

Whitelisting notes: 

- white: pages with minimal cross outs and double text notes, could expect a program to do well on this
- gray: pages with lots of cross outs and notes, a program might have trouble with this
- black: none yet, but stuff with lots of rearranging, transcription is wrong, no program could be expected to transcribe this

But I'll probably change it in the future to 
- white: actually good; no cross outs or text notes
- gray: minimal cross outs and notes
- black: lots of cross outs, any amount of rearrangement. 
