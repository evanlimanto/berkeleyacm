/*
 * POJ3469_ISAPalt.c
 *
 * Copyright 2013 Chen Ruichao <linuxer.sheep.0x@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define maxN 20000
#define maxM 200000
#define maxV (maxN+2)
#define maxE ((maxN*2+maxM)<<1)

int V, hdr[maxV], nxt[maxE], dst[maxE], cap[maxE];

int calcMaxFlow(void)
{
    static int h[maxV], hcnt[maxV+1];
    static int cur[maxV];
    static int Stop, eS[maxV-1];
    int res=0;
    int u,e,i,f;

    memset(cur, -1, sizeof(cur[0])*V);
    memset(h, 0, sizeof(h[0])*V);
    memset(hcnt, 0, sizeof(hcnt[0])*V); /* no need to set hcnt[V] */
    hcnt[0]=V;

    Stop=0;
    while(h[0]<V) {
        u = Stop==0 ? 0 : dst[eS[Stop-1]];
        if(u == V-1) {
            f = INT32_MAX;
            for(i=0;i<Stop;i++)
                if(f > cap[eS[i]])
                    f = cap[eS[i]];
            while(Stop>0) {
                Stop--;
                cap[eS[Stop]  ] -= f;
                cap[eS[Stop]^1] += f;
            }
            res+=f;
            continue;
        }
        if(cur[u] == -1) cur[u] = hdr[u];
        for(e=cur[u]; e!=-1; e=nxt[e])
            if(cap[e]>0 && h[dst[e]] == h[u]-1)
                break;
        cur[u]=e;
        if(e!=-1) {
            eS[Stop++] = e;
        } else {
            if(--hcnt[h[u]] == 0) break;
            h[u]++;
            hcnt[h[u]]++;
            if(Stop>0) Stop--;
        }
    }

    return res;
}

void connect(int s, int d, int c)
{
    static int e=0;
    cap[e]=c;
    dst[e]=d;
    nxt[e]=hdr[s];
    hdr[s]=e++;
}

int main(void)
{
    int N,M;
    int u,v,c,a,b;

    /* 0, N+1 represent CoreA, CoreB respectively */
    scanf("%d%d",&N,&M);
    V=N+2;
    memset(hdr, -1, sizeof(hdr[0])*V);
    for(v=1;v<=N;v++) {
        scanf("%d%d",&a,&b);
        connect(v, N+1, a);
        connect(N+1, v, 0);
        connect(0, v, b);
        connect(v, 0, 0);
    }
    while(M--) {
        scanf("%d%d%d",&u,&v,&c);
        connect(u, v, c);
        connect(v, u, c);
    }

    printf("%d\n", calcMaxFlow());

    return 0;
}
