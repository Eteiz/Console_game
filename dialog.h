//
// Created by MrsRo on 27.12.2022.
//

#ifndef CONSOLE_GAME_DIALOG_H
#define CONSOLE_GAME_DIALOG_H

enum dialog_state {
    DIALOG_0,
    DIALOG_1,
    DIALOG_2,
    DIALOG_3,
    DIALOG_4,
    REST
};

char game_dialog[][150] = {

        // First interaction
        {"\"...I have never heard such name before...\""},
        {"\"It's been so long since I have seen any living soul down there\""},
        {"\"However, this place will not give you what you seek, there's no point in you being here\""},
        {"\"Turn around and return to overworld if you know what's good for you\""},
        {"\"I cannot let you stay here\""},

        // Second interaction
        {"\"After the last human went through the barrier, all fell into the darkness and despair\""},
        {"\"All those monsters...all this hope..\""},
        {"\"...it all vanquished and turned into dust\""},

        // Third interaction
        {"\"One of few things that remained were the pieces of determination left by the said human...\""},
        {"\"...shining in the dark, waiting to be combined with monster soul\""},
        {"\"We could not let this happen, not after what Our King went through\""},

        // Fourth interaction
        {"\"The legends said that when human determination combines with monster soul...\""},
        {"\"...the results are catastrophic\""},
        {"\"The creature with such power could bring an end to all of the worlds\""},
        {"\"An end to remaining monster race\""},

        // Fifth interaction
        {"\"Me...along with some of the monsters that survived have said our vows...\""},
        {"\"...to sacrifice our lives to guard those pieces\""},
        {"\"So they would not fall into the hands of anyone, human or monster\""},
        {"\"I do not fear death if it means dying for my beliefs..\""},
        {"\"I do not fear death if it means not letting you get them!\""},

        // Rest of dialogue
        {"\"...\""},
        {"\"......\""},
        {"\"....\""},

        // Ending by attacking
        {"\"What...what are you?\""},
        {"\"Those eyes...they are not of monster nor human...\""},
        {"\"I...I can't l-let you get past me...\""},
        {"\"I..I can't...\""},
        {"\"...\""},
        {"\"...haha\""},
        {"\"I know what you are...\""},
        {"\"I know what you want to do\""},
        {"\"...and it won't work...\""},
        {"\"My brothers...they will succeed where I failed...\""},
        {"\"haha...\""},
        {"\"ha...ha...\""},
        {"\"...ha...\""},

        // Ending by talking
        {"\"Please,please stop this\""},
        {"\"I can't let another creature get absorbed by power...\""},
        {"\"Any blood...human or monster...shall not be spilled in another war...\""},
        {"\"...\""},
        {"\"...please...\""},
        {"\"...\""},
        {"\"......\""},
        {"\"No...\""},
        {"\"...this isn't right...\""},
        {"\"You deserve to retrieve what is of your kind...\""},
        {"\"...you are the ones that can handle its power best\""},
        {"\"...I shall let you pass\""},
        {"\"...the destruction of humans and monsters is in your hands...\""},

        // Starting screen
        {"You open your eyes only to notice you are surrounded by a complete darkness"},
        {"The only source of light is the fading blink in the distance"},
        {"You don't remember how or why you got here"},
        {"While trying to make any sense out of it, you hear an unfamiliar sound"},
        {"And then another"},
        {"The sounds become louder and louder, the source of it must be getting closer"},
        {"Suddenly, you notice a shadowy figure, shaped like a blob, in front of you"},
        {"..."},
        {"You point you blade towards it"},
        {"\"Fear not, I am not here to hurt you\""},
        {"\"I am The Guardian of this place, I need to know who you are\""},

        // Ending screen
        {"You get past The Guardian into the complete darkness"},
        {"You can't see anything - it is as if you had your eyes closed"},
        {"Suddenly, you can notice a faint light in the distance"},
        {"You walk slowly towards it, not even knowing if you have a ground below your feet"},
        {"..."},
        {"Here it is, before you eyes, a piece of determination"},
        {"You reach out to it"},
        {"Your body absorbs the piece, which connects with your heart"},
        {"Filled with power beyond you comprehension, you start to feel dizzy..."},
        {"...Not even knowing how and when, you faint"}
};

#endif //CONSOLE_GAME_DIALOG_H
