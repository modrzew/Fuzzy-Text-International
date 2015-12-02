#include "num2words.h"
#include "strings-ca.h"
#include "strings-de.h"
#include "strings-en_GB.h"
#include "strings-en_US.h"
#include "strings-es.h"
#include "strings-fr.h"
#include "strings-no.h"
#include "strings-pl.h"
#include "strings-sv.h"
#include "string.h"

size_t min(const size_t a, const size_t b) {
  return a < b ? a : b;
}

static size_t append_string(char* buffer, const size_t length, const char* str) {
  strncat(buffer, str, length);

  size_t written = strlen(str);
  return (length > written) ? written : length;
}

static size_t interpolate_and_append(char* buffer, const size_t length,
    const char* parent_str, const char* first_placeholder_str, const char* second_placeholder_str) {
  const char* placeholder_str;
  char* insert_ptr = strstr(parent_str, "$1");

  if (insert_ptr) {
    placeholder_str = first_placeholder_str;
  }
  else {
    insert_ptr = strstr(parent_str, "$2");
    placeholder_str = second_placeholder_str;
  }

  size_t parent_len = strlen(parent_str);
  size_t insert_offset = insert_ptr ? (size_t) insert_ptr - (size_t) parent_str : parent_len;

  size_t remaining = length;

  remaining -= append_string(buffer, min(insert_offset, remaining), parent_str);
  remaining -= append_string(buffer, remaining, placeholder_str);
  if (insert_ptr) {
    remaining -= append_string(buffer, remaining, insert_ptr + 2);
  }

  return remaining;
}

/* simple base 10 only itoa, found: http://stackoverflow.com/questions/20435527 */
char * itoa10(int value, char *result)
{
  char const digit[] = "0123456789";
  char *p = result;
  if (value < 0) {
    *p++ = '-';
    value *= -1;
  }

  /* move number of required chars and null terminate */
  int shift = value;
  do {
    ++p;
    shift /= 10;
  } while (shift);
  *p = '\0';

  /* populate result in reverse order */
  do {
    *--p = digit [value % 10];
    value /= 10;
  } while (value);

  return result;
}

const char* get_hour(Language lang, int index) {
  switch (lang) {
    case CA:
      return HOURS_CA[index];
    case DE:
      return HOURS_DE[index];
    case EN_GB:
      return HOURS_EN_GB[index];
    case ES:
      return HOURS_ES[index];
    case FR:
      return HOURS_FR[index];
    case NO:
      return HOURS_NO[index];
    case SV:
      return HOURS_SV[index];
    case PL:
      return HOURS_PL[index];
    default:
      return HOURS_EN_US[index];
  }
}

const char* get_hour_genitive(Language lang, int index) {
  switch (lang) {
    case PL:
      return HOURS_PL_GENITIVE[index];
    default:
      return get_hour(lang, index);
  }
}

int is_genitive(Language lang, int index) {
  switch (lang) {
    case PL:
      return RELS_PL_GENITIVE[index];
    default:
      return 0;
  }
}

const char* get_rel(Language lang, int index) {
  switch (lang) {
    case CA:
      return RELS_CA[index];
    case DE:
      return RELS_DE[index];
    case EN_GB:
      return RELS_EN_GB[index];
    case ES:
      return RELS_ES[index];
    case FR:
      return RELS_FR[index];
    case NO:
      return RELS_NO[index];
    case SV:
      return RELS_SV[index];
    case PL:
      return RELS_PL[index];
    default:
      return RELS_EN_US[index];
  }
}

void time_to_words(Language lang, int hours, int minutes, int seconds, char* words, size_t buffer_size) {

  size_t remaining = buffer_size;
  memset(words, 0, buffer_size);

  // We want to operate with a resolution of 30 seconds.  So multiply
  // minutes and seconds by 2.  Then divide by (2 * 5) to carve the hour
  // into five minute intervals.
  int half_mins  = (2 * minutes) + (seconds / 30);
  int rel_index  = ((half_mins + 5) / (2 * 5)) % 12;
  int hour_index;

  if (rel_index == 0 && minutes > 30) {
    hour_index = (hours + 1) % 24;
  }
  else {
    hour_index = hours % 24;
  }

  const char* rel  = get_rel(lang, rel_index);
  const char* hour;
  const char* next_hour;
  if (is_genitive(lang, rel_index)) {
    hour = get_hour_genitive(lang, hour_index);
    next_hour = get_hour_genitive(lang, (hour_index + 1) % 24);
  } else {
    hour = get_hour(lang, hour_index);
    next_hour = get_hour(lang, (hour_index + 1) % 24);
  }

  remaining -= interpolate_and_append(words, remaining, rel, hour, next_hour);

  // Leave one space at the end
  remaining -= append_string(words, remaining, " ");

}

const char* get_day(Language lang, int index) {
  switch (lang) {
    default:
      return DAYS_EN_US[index];
  }
}

const char* get_month(Language lang, int index) {
  switch (lang) {
    default:
      return MONTHS_EN_US[index];
  }
}

void date_to_words(Language lang, int day, int date, int month, char* words, size_t buffer_size) {
  size_t remaining = buffer_size;
  memset(words, 0, buffer_size);
  
  const char* stringday = get_day(lang, day);
  const char* stringmonth = get_month(lang, month);
  
  char stringdate[15];
  itoa10(date, stringdate);
  
  remaining -= append_string(words, remaining, stringday);
  remaining -= append_string(words, remaining, "  ");
  remaining -= append_string(words, remaining, stringmonth);
  remaining -= append_string(words, remaining, " ");
  remaining -= append_string(words, remaining, stringdate);
  remaining -= append_string(words, remaining, " ");
}