# String-Validity
_Indexing, extracting, and splicing a string to determine its validity under a set of rules.__

On various toll roads throughout the United States, transponders are used to identify vehicles and calculate tolls.
Suppose that FasTrak received the following vehicle string as cars passed by a transponder station: 8ABC001:2-55

The first part of the string corresponds to the vehicle's license plate, which in the example above was 8ABC001. For the purposes of this assignment, valid California license plates will have the format acccnnn, where a is a digit 1-9 and each is a digit 0-9 and each c is a letter A-Z. Following the colon (:) separator is the number of occupants in the vehicle, which in the example above meant 2 occupants. Following the dash (-) separator, a number appears which tells the speed of the vehicle, which in the example above was 55 miles/hour. The opening digit is the license series. The three letters following the license series is the letter group. Three digits following the letter group is the license group.

Rules for a valid vehicle string:

1. the license series must be in the range from 1-9.
2. the letter group must be all UPPERCASE alphabet characters.
3. the license number group must be in the range from 0-999.
4. the number of occupants must be 1 or more.
5. the speed must be a in the range from 1-999.

**Objective: implement the functions to return the correct results for varying vehicle strings.**
