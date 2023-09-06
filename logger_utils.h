#pragma once

#include <time.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

const std::string barrier = " >> ";

std::string get_time() {
	time_t result = time(NULL);
	char str[26];
	ctime_s(str, sizeof(str), &result);
	std::string new_str(str);
	new_str.pop_back();
	return(new_str);
};

enum COLOR {
	RED,
	BLUE,
	GREEN,
	YELLOW,
	PURPLE,
	WHITE
};

enum MODE {
	TRACE,
	INFO,
	DEBUG,
	WARNING,
	ERRORS
};

COLOR mode_to_color(const MODE& mode) {
	switch (mode) {
	case TRACE:   return WHITE;
		break;
	case INFO:    return BLUE;
		break;
	case WARNING: return YELLOW;
		break;
	case DEBUG:   return PURPLE;
		break;
	case ERRORS:  return RED;
		break;
	default:      return WHITE;
		break;
	}
};

std::string mode_to_string(const MODE& mode) {
	switch (mode) {
	case TRACE:   return " TRACE: ";
		break;
	case INFO:    return " INFO: ";
		break;
	case WARNING: return " WARNING: ";
		break;
	case DEBUG:   return " DEBUG: ";
		break;
	case ERRORS:  return " ERROR: ";
		break;
	default:      return " ";
		break;
	}
};

std::string color_code(const COLOR& color) {
	switch (color) {
	case RED:    return "\033[31m";
		break;
	case BLUE:   return "\033[34m";
		break;
	case GREEN:  return "\033[32m";
		break;
	case YELLOW: return "\033[33m";
		break;
	case WHITE:  return "\033[37m";
		break;
	case PURPLE: return "\033[35m";
		break;
	default:     return "\033[37m";
		break;
	}
};

void reset_color(std::ostream& str) {
	str << color_code(WHITE) + " ";
};

std::string paint_str(const std::string& str, const COLOR& color) {
	return (color_code(color) + str);
};


std::string general_line(const MODE& mode, bool colored = true) {
	std::string line = get_time() + " " + barrier;
	if (colored) {
		line = paint_str(line, WHITE);
		line += paint_str(mode_to_string(mode), mode_to_color(mode));
	}
	else {
		line += mode_to_string(mode);
	}
	return line;
};



