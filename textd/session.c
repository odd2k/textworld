#include "session.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static session **array = NULL;
size_t sessioncap = 0;

session *getsession(int sock)
{
	if(sock >= sessioncap)
		return NULL;

	return array[sock];
}

int quitsession(int sock)
{
	session *s;

	s = getsession(sock);
	if(s == NULL) {
		fprintf(stderr, "Quitting non-existent session.\n");
		return;
	}
	close(sock);
	array[sock] = NULL;
	free(s);
}

// TODO set view dimension
// TODO set position
session *makesession(int sock)
{
	session *s;
	size_t off;

	s = calloc(1, sizeof(session));

	s->sock = sock;
	s->w = 80;
	s->h = 24;

	if(sessioncap <= sock) {
		off = sessioncap;
		if(sessioncap == 0)
			sessioncap = 1;
		while(sessioncap <= sock)
			sessioncap <<= 1;
		array = realloc(array, sizeof(session *) * sessioncap);
		memset(array + off, 0, (sessioncap - off) * (sizeof(session *)));
	}
	printf("%d\n", sock);
	array[sock] = s;

	return s;
}
