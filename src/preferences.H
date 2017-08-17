// Preference types and settings

// structure holding preference values
struct pref_type {
  int back_color;
  int norm_color;
  int real_color;
  int imag_color;
  int intg_color;
};

extern pref_type gen_prefs;

// preferences file name
#define preferences_file "spex.conf"

// functions to handle preference files
void load_prefs(void);
void save_prefs(void);

