#include "strings-en_US.h"

const char* const HOURS_PL[] = {
  // AM hours
  "dwunasta",
  "pierwsza",
  "druga",
  "trzecia",
  "czwarta",
  "piąta",
  "szósta",
  "siódma",
  "ósma",
  "dziewiąta",
  "dziesiąta",
  "jedenasta",

  // PM hours
  "dwunasta",
  "pierwsza",
  "druga",
  "trzecia",
  "czwarta",
  "piąta",
  "szósta",
  "siódma",
  "ósma",
  "dziewiąta",
  "dziesiąta",
  "jedenasta",
};

const char* const HOURS_PL_GENITIVE[] = {
  // AM hours
  "dwunastej",
  "pierwszej",
  "drugiej",
  "trzeciej",
  "czwartej",
  "piątej",
  "szóstej",
  "siódmej",
  "ósmej",
  "dziewiątej",
  "dziesiątej",
  "jedenastej",

  // PM hours
  "dwunastej",
  "pierwszej",
  "drugiej",
  "trzeciej",
  "czwartej",
  "piątej",
  "szóstej",
  "siódmej",
  "ósmej",
  "dziewiątej",
  "dziesiątej",
  "jedenastej",
};


/**
 * The string "$1" will be replaced with the current hour (e.g., "three"
 * at 3:45).  The string "$2" will be replaced with the *next* hour
 * (e.g., "four" at 3:45).
 *
 * A "*" character before a word makes that word bold.
 */
const char* const RELS_PL[] = {
  "*$1",
  "pięć po *$1",
  "dziesięć po *$1",
  "kwadrans po *$1",
  "dwadzieścia po *$1",
  "za pięć wpół do *$2",
  "wpół do *$1",
  "pięć po wpół do *$2",
  "za dwadzieścia *$2",
  "za kwadrans *$2",
  "za dziesięć *$2",
  "za pięć *$2"
};

const int const RELS_PL_GENITIVE[] = {
    0,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    0,
    0,
    0,
    0
};
