/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef GUAC_KUBERNETES_H
#define GUAC_KUBERNETES_H

#include "config.h"
#include "common/clipboard.h"
#include "common/recording.h"
#include "settings.h"
#include "terminal/terminal.h"

#include <libwebsockets.h>
#include <stdint.h>

/**
 * The name of the WebSocket protocol specific to Kubernetes which should be
 * sent to the Kubernetes server when attaching to a pod.
 */
#define GUAC_KUBERNETES_LWS_PROTOCOL "v4.channel.k8s.io"

/**
 * The index of the Kubernetes channel used for STDIN.
 */
#define GUAC_KUBERNETES_CHANNEL_STDIN 0

/**
 * The index of the Kubernetes channel used for STDOUT.
 */
#define GUAC_KUBERNETES_CHANNEL_STDOUT 1

/**
 * The index of the Kubernetes channel used for STDERR.
 */
#define GUAC_KUBERNETES_CHANNEL_STDERR 2

/**
 * The index of the Kubernetes channel used for terminal resize messages.
 */
#define GUAC_KUBERNETES_CHANNEL_RESIZE 4

/**
 * Kubernetes-specific client data.
 */
typedef struct guac_kubernetes_client {

    /**
     * Kubernetes connection settings.
     */
    guac_kubernetes_settings* settings;

    /**
     * The connected WebSocket.
     */
    struct lws* wsi;

    /**
     * The Kubernetes client thread.
     */
    pthread_t client_thread;

    /**
     * The current clipboard contents.
     */
    guac_common_clipboard* clipboard;

    /**
     * The terminal which will render all output from the Kubernetes pod.
     */
    guac_terminal* term;

    /**
     * The in-progress session recording, or NULL if no recording is in
     * progress.
     */
    guac_common_recording* recording;

} guac_kubernetes_client;

/**
 * Main Kubernetes client thread, handling transfer of STDOUT/STDERR of an
 * attached Kubernetes pod to STDOUT of the terminal.
 */
void* guac_kubernetes_client_thread(void* data);

#endif
