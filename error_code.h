#pragma once
enum Error_code {
	success, fail, utility_range_error, underflow, overflow, fatal,
	not_present, duplicate_error, entry_inserted, entry_found,
	internal_error, div_by_zero, crash
};