"""Polite, disk-cached HTTP fetcher (stdlib only)."""
import hashlib
import os
import time
import urllib.error
import urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CACHE = os.path.join(ROOT, "data", "cache")
UA = ("Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 "
      "(KHTML, like Gecko) Chrome/126.0 Safari/537.36")
_last = {}


def fetch(url, delay=1.0, retries=4, refresh=False, binary=False):
    """GET url, caching the body under data/cache. Returns str (or bytes)."""
    key = hashlib.sha1(url.encode()).hexdigest()
    path = os.path.join(CACHE, key[:2], key)
    if not refresh and os.path.exists(path):
        data = open(path, "rb").read()
        return data if binary else data.decode("utf-8", "replace")
    host = url.split("/")[2]
    for attempt in range(retries):
        wait = _last.get(host, 0) + delay - time.time()
        if wait > 0:
            time.sleep(wait)
        _last[host] = time.time()
        try:
            req = urllib.request.Request(url, headers={"User-Agent": UA})
            with urllib.request.urlopen(req, timeout=40) as r:
                data = r.read()
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with open(path, "wb") as f:
                f.write(data)
            return data if binary else data.decode("utf-8", "replace")
        except urllib.error.HTTPError as e:
            if e.code == 404:
                return None
            err = e
        except Exception as e:  # timeouts, resets
            err = e
        time.sleep(5 * (attempt + 1))
    raise RuntimeError("fetch failed: %s (%s)" % (url, err))
