#ifndef stegosaurus_URIS_H
#define stegosaurus_URIS_H

#include "lv2/lv2plug.in/ns/ext/state/state.h"
#include "lv2/lv2plug.in/ns/ext/log/log.h"

#define LV2_MIDI__MidiEvent "http://lv2plug.in/ns/ext/midi#MidiEvent"
#define stegosaurus_URI "http://nickbailey.co.nr/plugins/stegosaurus"


typedef struct {
    LV2_URID midi_Event;
} stegosaurusURIs;

static inline void map_stegosaurus_uris(LV2_URID_Map* map, stegosaurusURIs* uris) {
    uris->midi_Event = map->map(map->handle, LV2_MIDI__MidiEvent);
}

#endif  /* stegosaurus_URIS_H */

